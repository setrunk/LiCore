#include "gisimageryprovider.h"
#include "globe.h"
#include "quadtreeprimitive.h"
#include "quadtreetile.h"
#include "globesurfacetile.h"
#include "liscene.h"
#include "lientity.h"
#include "limaterial.h"
#include "litexture.h"
#include "litextureimage.h"
#include "lishader.h"
#include "lishaderprogram.h"
#include "litransform.h"
#include "lirenderstate.h"
#include "liviewer.h"
#include "liengine.h"
#include "lirendersystem.h"
#include "licamera.h"
#include "ligeometry.h"
#include "licomputerenderer.h"
#include "liviewportquadrenderer.h"
#include "liutils.h"
#include "asyncfuture.h"
#include "transformhelper.h"
#include "imagery.h"
#include "geographictilingscheme.h"
#include <qgis.h>
#include <qgsvectorlayer.h>
#include <qgsmapsettings.h>
#include <qgsmaprendererparalleljob.h>
#include <qgsmaprenderersequentialjob.h>
#include <qgsproject.h>
#include "framerecord_p.h"
#include "timestamp.h"
#include "liworkerthread.h"

inline quint64 makeKey(int x, int y, int level)
{
    return (quint64(level) << 58) | (quint64(y) << 29) | quint64(x);
}

GisImageryProvider::GisImageryProvider(LiNode *parent)
    : LiBehavior(parent)
{
    Globe *globe = GlobalViewer()->scene()->globe();

    connect(globe->surface(), &QuadtreePrimitive::tileDeleted, this, [this](QuadtreeTile *tile) {
        quint64 key = makeKey(tile->x(), tile->y(), tile->level());
        if (_dataHash.contains(key))
        {
            auto it = _dataHash.value(key);
            _dataHash.remove(key);

            if (it->state == Loading)
            {
                it->tile = nullptr;
                it->state = Removed;
            }
            else
            {
                delete it;
            }
        }
    });
}

void GisImageryProvider::update()
{
    Globe *globe = GlobalViewer()->scene()->globe();
    const auto &tiles = globe->surface()->tilesToRender();
    for (QuadtreeTile *tile : tiles)
    {
        if (!tile->rectangle().intersected(_extent))
            continue;

        if (tile->rectangle().width() > _extent.width() * 2 && tile->rectangle().height() > _extent.height() * 2)
            continue;

        auto surfaceTile = tile->data();
        if (!surfaceTile->decalTexture())
        {
            quint64 key = makeKey(tile->x(), tile->y(), tile->level());
            auto it = _dataHash.value(key, nullptr);
            if (!it)
            {
                it = new TileData;
                it->state = Start;
                it->key = key;
                it->texture = nullptr;
                it->tile = tile;
                it->rectangle = tile->rectangle();
                _dataHash.insert(key, it);
            }

            if (it->state == Start)
            {
                it->state = Loading;
                requestImage(it);
            }

            if (it->state == Ready)
            {
                surfaceTile->setDecalTexture(it->texture);
            }
            else
            {
                surfaceTile->setDecalTexture(nullptr);
            }
        }
    }
}

void GisImageryProvider::requestImage(TileData *tileData)
{
    if (!_thread)
        _thread = new LiWorkerThread();

    auto p = _thread->runTask([=] {
        const int imageSize = 256;
        auto rect = tileData->rectangle.toDegrees(); //tile->rectangle.toDegrees();
        QgsRectangle extent(rect.west,
                            rect.south,
                            rect.east,
                            rect.north);

        QgsMapSettings settings;
        settings.setDestinationCrs(*TransformHelper::instance()->WGS84());
        settings.setLayers(_layers);
        settings.setExtent(extent);
        settings.setOutputSize(QSize(imageSize, imageSize));
        settings.setBackgroundColor(Qt::transparent);
        settings.setFlag(QgsMapSettings::Antialiasing);
        settings.setFlag(QgsMapSettings::UseRenderingOptimization);
        settings.setFlag(QgsMapSettings::ForceVectorOutput);
        settings.setFlag(QgsMapSettings::RenderPartialOutput);

        QgsMapRendererSequentialJob *job = new QgsMapRendererSequentialJob(settings);
        connect(job, &QgsMapRendererJob::finished, this, [job, tileData] {
            QImage image = job->renderedImage();
            job->deleteLater();

            if (tileData->state == Removed)
            {
                delete tileData;
            }
            else
            {
                LiTextureImage *ti = new LiTextureImage();
                auto promise = ti->setImage(image, true);

                observe(promise).subscribe([ti, tileData] {
                    if (tileData->state == Removed)
                    {
                        ti->deleteLater();
                        delete tileData;
                    }
                    else
                    {
                        LiTexture *tex = new LiTexture();
                        tex->addTextureImage(ti);
                        tex->setWrapModeS(LiTexture::ClampToEdge);
                        tex->setWrapModeT(LiTexture::ClampToEdge);
                        tex->setMagnificationFilter(LiTexture::Linear);
                        tex->setMinificationFilter(LiTexture::LinearMipMapLinear);
                        tex->setMaximumAnisotropy(16);
                        tileData->texture = tex;
                        tileData->state = Ready;
                    }
                });
            }
        });

        job->start();
    });

//    observe(p).subscribe([] {
//        qDebug() << "job done.";
//    });
}

void GisImageryProvider::addLayer(QgsMapLayer *layer)
{
    if (!_layers.contains(layer))
    {
//        auto crs = layer->crs();
//        int srcId = crs.srsid();
//        auto wgs84 = TransformHelper::instance()->WGS84();
//        int dstId = wgs84->srsid();
//        auto context = QgsProject::instance()->transformContext();
//        context.addSourceDestinationDatumTransform(crs, *wgs84, srcId, dstId);
//        QgsProject::instance()->setTransformContext(context);

        _layers.append(layer);

        LiRectangle rectangle = TransformHelper::instance()->toWgs84(layer->extent(), &layer->crs());

        connect(layer, &QgsMapLayer::repaintRequested, this, [this, rectangle] {
            repaint(rectangle, false);
        });

        auto conne = connect(layer, &QgsMapLayer::willBeDeleted, this, [this, layer] {
            removeLayer(layer);
        });
        _connections[layer] = conne;

        if (_extent.isNull())
            _extent = rectangle;
        else
            _extent.combine(rectangle);

        repaint(rectangle, true);
    }
}

void GisImageryProvider::removeLayer(QgsMapLayer *layer)
{
    if (_layers.removeOne(layer))
    {
        _connections.remove(layer);

        _extent = LiRectangle();
        if (_layers.size())
        {
            auto l = _layers.first();
            _extent = TransformHelper::instance()->toWgs84(l->extent(), &l->crs());
        }
        for (int i = 1; i < _layers.size(); ++i)
        {
            auto l = _layers.at(i);
            _extent.combine(TransformHelper::instance()->toWgs84(l->extent(), &l->crs()));
        }

        LiRectangle rect = TransformHelper::instance()->toWgs84(layer->extent(), &layer->crs());
        repaint(rect, false);
    }
}

void GisImageryProvider::repaint(const LiRectangle &extent, bool add)
{
    const auto keys = _dataHash.keys();
    for (auto key : keys)
    {
        TileData *tile = _dataHash[key];
        if (!add && tile->emptyImage)
            continue;

        if (extent.intersected(tile->rectangle))
        {
            if (tile->tile)
            {
                tile->tile->data()->setDecalTexture(nullptr);
            }

            if (tile->texture)
            {
                tile->texture->deleteLater();
                tile->texture = nullptr;
            }

            if (tile->state == Loading)
            {
                TileData *tile2 = new TileData;
                tile2->key = tile->key;
                tile2->tile = tile->tile;
                tile2->rectangle = tile->rectangle;
                _dataHash[key] = tile2;

                tile->state = Removed;
            }
            else
            {
                tile->state = Start;
                tile->emptyImage = false;
            }
        }
    }
}

GisImageryProvider::TileData::~TileData()
{
    if (texture)
        texture->deleteLater();
}
