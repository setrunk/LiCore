#include "sample.h"
#include <liengine.h>
#include <litimesystem.h>
#include "globe.h"
#include "terrainsurfacelayer.h"
#include "lientity.h"
#include "litransform.h"
#include "licamera.h"
#include "liforest.h"
#include "li3dtileset.h"
#include "lisceneiofactory.h"
#include "lisceneloader.h"
#include "liraycasthit.h"
#include "imagerylayer.h"
#include "terrainprovider.h"
#include "wmsimageryprovider.h"
#include "asyncfuture.h"
#include "timestamp.h"
#include "liquadtreetileset.h"
#include "liutils.h"
#include "litextureprojection.h"
#include "litexture.h"
#include "litextureimage.h"
#include "transforms.h"
#include "lilight.h"
#include <livectorlayer.h>
#include <litreelayer.h>
#include <liviewer.h>
#include <liengine.h>
#include <liframeaction.h>
#include <liinputsystem.h>
#include <lipickid.h>
#include <lifeature.h>
#include <liviewshed.h>
#include <liwidget.h>
#include <liplanegeometry.h>
#include <limaterial.h>
#include <lishaderprogram.h>
#include <liheatmap.h>
#include <liheatmaplayer.h>
#include <gisimageryprovider.h>
#include <liclipvolume.h>
#include <liflattenmask.h>
#include "li3dtile.h"
#include "lirenderstate.h"
#include "limesh.h"
#include "lianimator.h"

#include <liparticlesystem.h>
#include <liimageparticlerenderer.h>
#include <emitters/liparticleemitter.h>
#include <directions/lipointdirection.h>
#include <extruders/lirectangleextruder.h>
#include <affectors/ligravityaffector.h>

class Fps : public LiBehavior
{
public:
    void update() override {
        static quint64 frameId = 0;
        static quint64 lastTime = 0;
        static quint64 lastFrameId = 0;

        quint64 t = GlobalViewer()->engine()->timeSystem()->timeStamp();

        if (t - lastTime > 1e6) {
            double t2 = (t - lastTime) * 1e-6;
            double fps = (frameId - lastFrameId) / t2;
            lastTime = t;
            lastFrameId = frameId;
            GlobalViewer()->widget()->widget()->setWindowTitle(QString("Viewer - fps(%1)").arg(int(fps+0.5)));
        }

        ++frameId;

        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
        if (input->getMouseButtonDown(Qt::LeftButton)) {
            LiCamera *camera = LiCamera::main();
            Vector3 pos = camera->transform()->worldPosition();
            qDebug() << "camera:" << pos.length();
        }
    }
};

void createFps()
{
    LiEntity *entity = new LiEntity;
    entity->addComponent(new Fps);
    GlobalViewer()->scene()->addEntity(entity);
}

void loadDEM(LiScene *scene)
{
//    scene->globe()->setTerrainProviderUrl("http://61.144.226.45:8084/Tile3D/B3DM/terrain");
//    scene->globe()->setTerrainProviderUrl("http://61.144.226.45:8084/Tile3D/B3DM/terrainmesh");
}

void loadDOM(LiScene *scene)
{
    // shenzhen DOM
    if (1)
    {        
        LiRectangle rectangle = LiRectangle::MAX_VALUE;
        QString url = "http://ag.szgeoinfo.com/arcgis/rest/services/szimage/MapServer?bbox=113.71108478300005,22.43722115999999,114.64990900400005,22.872570290999988";
//        QString url = "http://suplicmap.pnr.sz/tilemap_1/rest/services/SZIMAGE/SZAVI2004_60ZW2K/ImageServer/exportImage?bbox=113.71108478300005,22.43722115999999,114.64990900400005,22.872570290999988";

        QUrlQuery query(url);
        QString value = query.queryItemValue("bbox");
        if (value.size())
        {
            QStringList l = value.split(QChar(','), QString::SkipEmptyParts);
            if (l.size() == 4)
            {
                double vals[4];
                for (int i = 0; i < 4; ++i)
                {
                    const QString &s = l.at(i);
                    vals[i] = s.toDouble();
                }

                rectangle = LiRectangle(vals[0], vals[1], vals[2], vals[3]).toRadians();
            }
        }

        ImageryProvider *imageryProvider = new WmsImageryProvider(url);
        ImageryLayer *imageryLayer = new ImageryLayer(imageryProvider, 0, 100, rectangle);
        scene->globe()->addImageryLayer(imageryLayer);



//        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
//        QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
//            if (key == Qt::Key_Q) {
//                bool show = imageryLayer->show();
//                imageryLayer->setShow(!show);
//            }
//       });
    }

    // futian DOM
    if (0)
    {
        ImageryProvider *imageryProvider = new WmsImageryProvider("http://61.144.226.45:8085/arcgis/rest/services/20171201/DOMserver2014/MapServer");
        ImageryLayer *imageryLayer = new ImageryLayer(imageryProvider);
        scene->globe()->addImageryLayer(imageryLayer);

        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
        QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
            if (key == Qt::Key_W) {
                bool show = imageryLayer->show();
                imageryLayer->setShow(!show);
            }
       });
    }

    // minzhi DOM
    if (0)
    {
        ImageryProvider *imageryProvider = new WmsImageryProvider("http://61.144.226.45:8085/arcgis/rest/services/20180614/minzhi_dom/MapServer");
        ImageryLayer *imageryLayer = new ImageryLayer(imageryProvider);
        scene->globe()->addImageryLayer(imageryLayer);

        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
        QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
            if (key == Qt::Key_E) {
                bool show = imageryLayer->show();
                imageryLayer->setShow(!show);
            }
       });
    }
}

void loadModel(LiScene *scene, const QString &path, const Cartographic &lonlat, double scale)
{
    int count = 1;
    for (int i = 0; i < count; ++i) {
        QUrl url = resolvedUrl(path);
        LiSceneLoader *loader = LiSceneIOFactory::createSceneLoader(QUrl(url.path()));
        if (loader)
        {
            QVariantMap options;
            auto promise = loader->load(url, options);
            observe(promise).subscribe([=]() {
                loader->deleteLater();
                LiEntity *entity = loader->scene();
                if (entity) {
                    LiAnimator *animator = entity->component<LiAnimator>();
                    if (animator) {
                        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
                        QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
                            if (key == Qt::Key_P) {
                                animator->setRunning(!animator->isRunning());
                            } else if (key == Qt::Key_N) {
                                int clip = (animator->currentClip() + 1) % animator->clipCount();
                                animator->setCurrentClip(clip);
                            } else if (key == Qt::Key_M) {
                                int mode = (animator->playMode() + 1) % 3;
                                animator->setPlayMode((LiAnimator::PlayMode)mode);
                            }
                        });
                    }
                    LiEntity *parentEntity = new LiEntity();
                    parentEntity->transform()->setCartographic(lonlat/*Cartographic::fromDegrees(114.054494, 22.540745, 0)*/);
                    entity->transform()->setPosition(Vector3(i*20, 0, 0));
                    entity->transform()->setScale(10);
                    entity->transform()->setRotation(Quaternion::fromAxisAndAngle(1,0,0,90));
                    entity->setParent(parentEntity);
                    scene->addEntity(parentEntity);
                }
            });
    }
    }
}

void loadTrees(LiScene *scene)
{
    // load from .STF file
    if (1)
    {
        LiForest *forest = new LiForest();
        forest->setBaseUrl(QUrl("file:///D:/work/LiEngine/others/trees/"));
        forest->load(QUrl("file:///D:/work/LiEngine/others/trees/szcenter.STF"));
        forest->setHeightMode(LiForest::RelativeToGround);
        forest->setAltitude(1.0);

        LiEntity *entity = new LiEntity();
        entity->transform()->setCartographic(Cartographic::fromDegrees(114.054494, 22.540745, 0));
        entity->addComponent(forest);
        scene->addEntity(entity);

        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
        QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
            static float roughness = 1.f;
            static float thickness = 0.5f;
            if (key == Qt::Key_F1) {
                float step = input->getKey(Qt::Key_Shift) ? 0.1f : 0.01f;
                roughness = std::min(1.f, roughness+step);
                forest->setProperty("roughness", roughness);
                qDebug() << forest->property("roughness").toDouble();
            }
            if (key == Qt::Key_F2) {
                float step = input->getKey(Qt::Key_Shift) ? 0.1f : 0.01f;
                roughness = std::max(0.f, roughness-step);
                forest->setProperty("roughness", roughness);
                qDebug() << forest->property("roughness").toDouble();
            }
            if (key == Qt::Key_F3) {
                float step = input->getKey(Qt::Key_Shift) ? 0.1f : 0.01f;
                thickness = std::min(1.f, thickness+step);
                forest->setProperty("thickness", thickness);
                qDebug() << forest->property("thickness").toDouble();
            }
            if (key == Qt::Key_F4) {
                float step = input->getKey(Qt::Key_Shift) ? 0.1f : 0.01f;
                thickness = std::max(0.f, thickness-step);
                forest->setProperty("thickness", thickness);
                qDebug() << forest->property("thickness").toDouble();
            }
        });
    }

    // load from vector layer
    if (0)
    {
//        QgsVectorLayer *vectorLayer = new QgsVectorLayer("C:/Users/apple/Documents/Projects/LiEngine/others/trees/tree.shp", "tree", "ogr", false);

//        // create tree layer
//        LiTreeLayer *treeLayer = new LiTreeLayer();
//        treeLayer->setAutoRotationAndScale(true);
//        treeLayer->setBaseUrl(QUrl("file:///C:/Users/apple/Dev/TeraScene/Data/Trees/"));
//        treeLayer->load(vectorLayer);

//        LiEntity *entity = new LiEntity();
//        entity->addComponent(treeLayer);
//        scene->addEntity(entity);

        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
        QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
            static bool loaded = false;
            if (loaded)
                return;

            if (key == Qt::Key_L) {
                loaded = true;

//                QgsVectorLayer *vectorLayer = new QgsVectorLayer("D:/work/LiEngine/others/trees/tree.shp", "tree");
                QgsVectorLayer *vectorLayer = new QgsVectorLayer(QString::fromLocal8Bit("D:/work/LiEngine/others/treeFT/市民中心北广场.shp"), "tree");

                // create tree layer
                LiTreeLayer *treeLayer = new LiTreeLayer();
                treeLayer->setHeightMode(LiForest::None);
                treeLayer->setAltitude(250.0);
                treeLayer->setAutoRotationAndScale(true);
                treeLayer->setBaseUrl(QUrl("file:///D:/download/TeraScene/Data/Trees/"));
                treeLayer->load(vectorLayer);
                scene->mainCamera()->flyTo(treeLayer->rectangle());

                LiEntity *entity = new LiEntity();
                entity->addComponent(treeLayer);
                scene->addEntity(entity);

            }
        });
    }
}


void flytoTileset(Li3DTileset *tileset)
{
    auto promise = tileset->readyPrimose();

    observe(promise).subscribe([=] {
        qDebug() << "tileset loaded.";

        auto scene = GlobalViewer()->scene();
        auto rect = tileset->rectangle();

        if (!rect.isNull()) {
            scene->mainCamera()->flyTo(tileset->rectangle());
        } else {
            auto root = tileset->root();
            if (root) {
                auto bounds = root->boundingVolume();
                scene->mainCamera()->flyTo(bounds.center());
            }
        }
    }, [] {
        qDebug() << "failed to load tileset.";
    });
}

void flattenMaskTileset(Li3DTileset *tileset)
{
    struct PickData
    {
        LiFlattenMask *flatten = nullptr;
        QVector<Vector3> points;
        bool done = false;
    };

    QVector<PickData> *pDataList = new QVector<PickData>();
    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();

    QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
        if (key == Qt::Key_F1) {
            PickData data;
            pDataList->append(data);
        }
        if (key == Qt::Key_F2) {
            if (pDataList->size()) {
                PickData &data = pDataList->last();
                data.points.append(data.points.first());
                data.done = true;

                LiFlattenMask *flatten = new LiFlattenMask();
                flatten->setPoints(data.points);
                tileset->addFlattenMask(flatten);
                data.flatten = flatten;

                QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
                    if (key == Qt::Key_F3) {
                        flatten->setEnabled(!flatten->isEnabled());
                    }
                });
            }
        }
        if (key == Qt::Key_F4) {
            if (pDataList->size()) {
                LiFlattenMask *flatten = pDataList->first().flatten;
                tileset->removeFlattenMask(flatten);
                flatten->deleteLater();
                pDataList->pop_front();
            }
        }
    });

    QObject::connect(input, &LiInputSystem::leftButtonDown, [=] {
        if (pDataList->size()) {
            PickData &data = pDataList->last();
            if (!data.done) {
                auto scene = GlobalViewer()->scene();
                Ray ray = scene->mainCamera()->screenPointToRay(input->mousePosition());
                LiRaycastHit hit;
                if (scene->raycast(ray, &hit)) {
                    data.points.append(hit.point());
                }
            }
        }
    });
}

void highlightTileset(Li3DTileset *tileset)
{
    QObject::connect(tileset, &Li3DTileset::contentLoaded, [](LiEntity *entity) {
        QStack<LiEntity*> stack;
        stack.push(entity);

        QVector<LiGeometryRenderer*> renderers;

        while (stack.size()) {
            LiEntity *e = stack.pop();
            auto renderer = e->renderer();

            if (renderer) {
                if (LiMesh *mesh = qobject_cast<LiMesh*>(renderer)) {
                    renderers.append(mesh->renderers());
                } else {
                    renderers.append(renderer);
                }

                for (auto r : renderers) {
                    LiMaterial *m = r->material();
                    if (m) {
                        m->setBothSided(true);
                        m->setOpacity(0.1);
                        m->renderState()->setBlendFuncSourceRgb(LiRenderState::SourceAlpha);
                        m->renderState()->setBlendFuncSourceAlpha(LiRenderState::SourceAlpha);
                        m->renderState()->setBlendFuncDestRgb(LiRenderState::One);
                        m->renderState()->setBlendFuncDestAlpha(LiRenderState::One);
                    }
                }

                renderers.resize(0);
            }

            stack.append(e->childEntities());
        }
    });
}

void moveTilesetByMouse(Li3DTileset *tileset)
{
    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();

    QObject::connect(input, &LiInputSystem::leftButtonDown, [=] {
        if (input->getKey(Qt::Key_Shift)) {
            auto scene = GlobalViewer()->scene();
            auto ray = scene->mainCamera()->screenPointToRay(input->mousePosition());
            LiRaycastHit hit;
            if (scene->raycast(ray, &hit)) {
                Vector3 pos = hit.point();
                tileset->setModelMatrix(eastNorthUpToFixedFrame(pos));
            }
        }
    });
}

void load3DTileset(LiScene *scene)
{
    Li3DTileset *tileset;
    LiEntity *entity;

    if (1)
    {
        tileset = new Li3DTileset(QString::fromLocal8Bit("D:/Models/香港机场/out/tileset.json"));
        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);
        flytoTileset(tileset);
    }


    if (0)
    {
        QStringList list;
        list << "http://61.144.226.45:8088/buildings/futian.39733/tileset.json"
             << "http://61.144.226.45:8088/buildings/futianbaimo/tileset.json"
             << "http://61.144.226.45:8088/buildings/xqcs/3dmax/ft-max-3dtiles/2012ftgxmx-2000-PY/tileset.json"
             << "http://61.144.226.45:8088/buildings/xqcs/BIM/bdxsjql2019-4-16/CZ_PD_D-1_GJZ_STR/tileset.json"
             << "http://61.144.226.45:8088/buildings/xqcs/qingxiedt/skjz-3dtiles/JZ2487-492/tileset.json"
             << "http://61.144.226.45:8088/buildings/feiducaozong/tileset.json"
             << "http://61.144.226.45:8088/buildings/CZNS_zch/tileset.json";

        for (const auto &uri : list)
        {
            tileset = new Li3DTileset(uri);
            tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
            entity = new LiEntity;
            entity->addComponent(tileset);
            scene->addEntity(entity);
        }
    }

    // futian
    if (0)
    {
//        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/futian.39733/tileset.json");
//        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/futianbaimo/tileset.json");
//        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/xqcs/3dmax/ft-max-3dtiles/2012ftgxmx-2000-PY/tileset.json");
//        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/xqcs/BIM/bdxsjql2019-4-16/CZ_PD_D-1_GJZ_STR/tileset.json");
//        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/xqcs/qingxiedt/skjz-3dtiles/JZ2487-492/tileset.json");
//        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/feiducaozong/tileset.json");
//        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/CZNS_zch/tileset.json");
        tileset = new Li3DTileset("http://68.68.12.43:8088/buildings/szbzqx/tileset.json");
        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
//        tileset->setAltitude(50.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)
//        tileset->setGenMeshNormals(true);
//        tileset->setForceTwoSided(true);
//        tileset->setDebugBoundingVolume(true);

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        flytoTileset(tileset);
//        flattenMaskTileset(tileset);
//        moveTilesetByMouse(tileset);
        highlightTileset(tileset);
    }

    // dalang
    if (0)
    {
        tileset = new Li3DTileset("http://61.144.226.45:8088/buildings/longhua/fuchengjiedao/02/tileset.json");
        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
        tileset->setAltitude(50.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)
//        tileset->setGenMeshNormals(true);

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        auto promise = tileset->readyPrimose();
        observe(promise).subscribe([] {
            qDebug() << "tileset loaded.";
        }, [] {
            qDebug() << "failed to load tileset.";
        });
    }

    // qing-xie
    if (0)
    {
        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/QX/tastqx/B3DM01/tileset.json");
        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
        tileset->setAltitude(-50.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        auto promise = tileset->readyPrimose();
        observe(promise).subscribe([] {
            qDebug() << "tileset loaded.";
        }, [] {
            qDebug() << "failed to load tileset.";
        });
    }

    // ghdx
    if (0)
    {
        tileset = new Li3DTileset("http://68.68.12.43:8088/buildings/futian/ghds/tileset.json");
        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
        tileset->setAltitude(25.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)
//        tileset->setDebugBoundingVolume(true);

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        auto promise = tileset->readyPrimose();
        observe(promise).subscribe([] {
            qDebug() << "tileset loaded.";
        }, [] {
            qDebug() << "failed to load tileset.";
        });
    }

    // futian
    if (0)
    {
        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/buildings/futian/2008/futianjiedao/01/tileset.json");

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        auto promise = tileset->readyPrimose();
        observe(promise).subscribe([] {
            qDebug() << "tileset loaded.";
        }, [] {
            qDebug() << "failed to load tileset.";
        });
    }

    // futian2
    if (0)
    {
        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/buildings/futian/futian.397336/tileset.json");
//        tileset = new Li3DTileset("file:///z:/tileset.json");
        tileset->setGenMeshNormals(true);
        tileset->setClampedTerrain(false);
//        tileset->setDebugBoundingVolume(true);

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        auto promise = tileset->readyPrimose();
        observe(promise).subscribe([] {
            qDebug() << "tileset loaded.";
        }, [] {
            qDebug() << "failed to load tileset.";
        });
    }

    // baoan
    if (0)
    {
        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/buildings/baoan.397334/tileset.json");
        tileset->setGenMeshNormals(true);
        tileset->setClampedTerrain(false);
        tileset->setForceTwoSided(true);
//        tileset->setGeometricErrorScale(2);
//        tileset->setStreamingMode(false);
//        tileset->setSkipLevelOfDetail(true);
//        tileset->setDebugBoundingVolume(true);

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        auto promise = tileset->readyPrimose();
        observe(promise).subscribe([] {
            qDebug() << "tileset loaded.";
        }, [] {
            qDebug() << "failed to load tileset.";
        });
    }

    // load roads tileset
    if (0)
    {
        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/road/tileset.json");
        tileset->setTerrainSurface(true); // 路网铺地模型，属于地形的一部分 (默认为false)
        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
        tileset->setAltitude(20.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)
        tileset->setTextureFlip(true);

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

//        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/roadviewLH/tileset.json");
//        tileset->setTerrainSurface(true); // 路网铺地模型，属于地形的一部分 (默认为false)
//        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
//        tileset->setAltitude(60.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)

//        entity = new LiEntity;
//        entity->addComponent(tileset);
//        scene->addEntity(entity);
    }

    // load buildings tileset
    if (0)
    {
//        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/buildings/futian/2008/futianjiedao/01/tileset.json");
//        tileset->setTerrainSurface(false); // 路网铺地模型，属于地形的一部分 (默认为false)
//        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
//        tileset->setAltitude(0.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)
//        tileset->setStreamingMode(true); // 默认为true

//        entity = new LiEntity;
//        entity->addComponent(tileset);
//        scene->addEntity(entity);

        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/minzhijiedao/01/tileset.json");
        tileset->setTerrainSurface(false); // 路网铺地模型，属于地形的一部分 (默认为false)
        tileset->setClampedTerrain(true); // 贴地模式 (默认为true)
        tileset->setAltitude(0.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)
        tileset->setStreamingMode(true); // 默认为true

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);

        tileset = new Li3DTileset("http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/minzhijiedao/02/tileset.json");
        tileset->setTerrainSurface(false); // 路网铺地模型，属于地形的一部分 (默认为false)
        tileset->setClampedTerrain(true); // 贴地模式 (默认为true)
        tileset->setAltitude(0.0); // 离地高度，该参数可以有用户界面实时调节 (默认为0)
        tileset->setStreamingMode(true); // 默认为true

        entity = new LiEntity;
        entity->addComponent(tileset);
        scene->addEntity(entity);
    }

    if (0)
    {
        QStringList paths;
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/minzhijiedao/01/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/minzhijiedao/02/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/fuchengjiedao/01/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/fuchengjiedao/02/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/guanhujiedao/01/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/guanhujiedao/02/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/guanlanjiedao/01/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/guanlanjiedao/02/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/longhuajiedao/01/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/longhuajiedao/02/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/dalangjiedao/01/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/dalangjiedao/02/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/minzhijiedao/01/tileset.json";
        paths << "http://61.144.226.45:8084/Tile3D/B3DM/buildings/longhua/minzhijiedao/02/tileset.json";

        for (const auto &path : paths)
        {
            tileset = new Li3DTileset(path);
//            tileset->setDebugBoundingVolume(true);

            entity = new LiEntity;
            entity->addComponent(tileset);
            scene->addEntity(entity);
        }
    }
}

void loadCarAnimation(LiScene *scene)
{
    QUrl url = resolvedUrl(QString::fromLocal8Bit("data/汽车超车.U3D"));
    QUrl mapUrl = QUrl::fromLocalFile("C:/Users/apple/Dev/TeraScene/textures/");

    LiSceneLoader *loader = LiSceneIOFactory::createSceneLoader(url);
    if (loader)
    {
        QVariantMap options;
        options["map_url"] = mapUrl;
        options["offset"] = Vector3(-114857, -19063, 0);
        auto future = loader->load(url, options);
        if (!future.isCanceled())
        {
            observe(future).subscribe([loader]() {
                loader->deleteLater();
                LiEntity *entity = loader->scene();
                if (entity)
                {
                    entity->transform()->setCartographic(Cartographic::fromDegrees(114.054494, 22.540745, 20));
                    entity->setParent(LiEntity::root());
                }
            });
        }
    }
}

void raycast(LiScene *scene)
{
    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
    QObject::connect(input, &LiInputSystem::leftButtonDown, [=] {
        auto s1 = getTimestamp();
        auto p = input->mousePosition();
        Ray ray = scene->mainCamera()->screenPointToRay(p.x(), p.y());
        LiRaycastHit hit;
        if (scene->raycast(ray, &hit))
        {
            auto s2 = getTimestamp();
            qDebug() << "ray cast point:" << hit.point().x() << hit.point().y() << hit.point().z();
        }
    });
}

void loadQuadtreeTileset()
{
    LiQuadtreeTileset *tileset;
    LiEntity *entity;

//    tileset = new LiQuadtreeTileset(QString::fromLocal8Bit("file:///J:/倾斜摄影数据/buxin/DAE/Data/LODTreeExport.xml"));
//    tileset->setTextureFlip(true);
//    tileset->setGenMeshNormals(true);
//    tileset->setClampedTerrain(false);
//    entity = new LiEntity(LiEntity::root());
//    entity->addComponent(tileset);

//    tileset = new LiQuadtreeTileset(QString::fromLocal8Bit("file:///J:/倾斜摄影数据/yulong/Productions/dae/Data/LODTreeExport.xml"));
//    tileset->setTextureFlip(true);
//    tileset->setGenMeshNormals(true);
//    tileset->setClampedTerrain(false);
//    entity = new LiEntity(LiEntity::root());
//    entity->addComponent(tileset);

//    tileset = new LiQuadtreeTileset(QString::fromLocal8Bit("file:///J:/倾斜摄影数据/mumianling/Productions/dae/Data/LODTreeExport.xml"));
//    tileset->setTextureFlip(true);
//    tileset->setGenMeshNormals(true);
//    tileset->setClampedTerrain(false);
//    entity = new LiEntity(LiEntity::root());
//    entity->addComponent(tileset);
}

void createTextureProjection()
{
    LiTextureImage *image = new LiTextureImage();
//    auto promise = image->loadImage(resolvedTextureUrl("qt-logo.png"));
    auto promise = image->loadImage(resolvedTextureUrl("test.jpg"));
    observe(promise).subscribe([image] {
        LiTexture *tex = new LiTexture2D();
        tex->addTextureImage(image);

        LiEntity *parentEntity = new LiEntity();
        parentEntity->transform()->setCartographic(Cartographic::fromDegrees(114.054494, 22.540745, 300));
        parentEntity->setParent(LiEntity::root());

        LiEntity *rotEnt = new LiEntity();
        rotEnt->setParent(parentEntity);
        rotEnt->transform()->setRotation(Quaternion::fromAxisAndAngle(1, 0, 0, -90));

        for (int i = -20; i <= 20; ++i)
        {
            LiTextureProjection *texProjection = new LiTextureProjection();
            texProjection->setTexture(tex);
            texProjection->setShowFrustum(true);
//            texProjection->setBlendMode(LiTextureProjection::AlphaBlend);
            texProjection->setSceneMode(LiTextureProjection::TerrainOnly);

            if (i % 2 == 0)
            {
                texProjection->setProjectionType(LiTextureProjection::Orthographic);
                texProjection->setOrthographicFrustum(100, 80);
            }
            else
            {
                texProjection->setProjectionType(LiTextureProjection::Perspective);
                texProjection->setPerspectiveFrustum(30, 1024.0/768.0);
            }

            LiEntity *entity = new LiEntity();
            entity->setParent(rotEnt);
            entity->transform()->setPosition(Vector3(i*200, 0, 0));
            entity->addComponent(texProjection);
        }
    });
}

void pickFeature(LiScene *scene)
{
    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();

    QObject::connect(input, &LiInputSystem::leftButtonDown, [=] {
        auto p = input->mousePosition();
        auto promise = scene->pickFeature(p);

        observe(promise).subscribe([=](LiPickId pickId) {
            qDebug() << "pickId:" << pickId.id();
            auto feature = scene->getFeatureByPickId(pickId);
            scene->setSelectedFeature(feature);
            if (feature) {
                const auto names = feature->propertyNames();
                for (const auto &name : names) {
                    qDebug() << name << ":" << feature->getProperty(name).toString();
                }
            }
        });
    });
}

void createViewshed(LiScene *scene)
{
    LiViewshed *viewshed = new LiViewshed();
    viewshed->setStart(Cartesian3::fromDegrees(114.054494, 22.540745, 100));
    viewshed->setEnd(Cartesian3::fromDegrees(114.064494, 22.540745, 0));
    viewshed->setShowDebugFrame(false);

    LiEntity *entity = new LiEntity();
    entity->addComponent(viewshed);
    scene->addEntity(entity);

    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();

    static bool editable = false;
    static bool pickStart = true;
    bool *pEditable = &editable;
    bool *pPickStart = &pickStart;

    QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
        if (key == Qt::Key_1) {
            *pEditable = !*pEditable;
            qDebug() << "editable:" << *pEditable;
        }
    });

    QObject::connect(input, &LiInputSystem::leftButtonDown, [=] {
        if (!*pEditable)
            return;

        auto p = input->mousePosition();
        Ray ray = scene->mainCamera()->screenPointToRay(p);
        LiRaycastHit hit;
        if (scene->raycast(ray, &hit)) {
            if (*pPickStart) {
                viewshed->setStart(hit.point());
                *pPickStart = false;
                qDebug() << "setStart";
            } else {
                viewshed->setEnd(hit.point());
                *pPickStart = true;
                qDebug() << "setEnd";
            }
        }
    });

    QObject::connect(input, &LiInputSystem::mouseMoving, [=] {
        if (!*pEditable)
            return;

        if (!*pPickStart) {
            auto p = input->mousePosition();
            Ray ray = scene->mainCamera()->screenPointToRay(p);
            LiRaycastHit hit;
            if (scene->raycast(ray, &hit)) {
                viewshed->setEnd(hit.point());
            }
        }
    });
}

void createPlane(LiScene *scene)
{
    LiPlaneGeometry *geometry = new LiPlaneGeometry();
    geometry->setWidth(1000);
    geometry->setHeight(1000);
    geometry->setResolution(QSize(10, 10));
    geometry->setTileUV(QSize(2, 4));
    geometry->create();

    LiTextureImage *texImage = new LiTextureImage();
    texImage->loadImage(resolvedTextureUrl("test.jpg"));
    LiTexture *tex = new LiTexture2D();
    tex->addTextureImage(texImage);

    LiMaterial *mat = new LiMaterial;
    mat->setTexture(tex);

    LiGeometryRenderer *renderer = new LiGeometryRenderer();
    renderer->setGeometry(geometry);
    renderer->setPrimitiveCount(600);
    renderer->setMaterial(mat);
    renderer->setCastShadow(true);
    renderer->setReceiveShadow(true);
    renderer->computeBoundingVolume();

    LiEntity *entity = new LiEntity();
    entity->addComponent(renderer);
    entity->transform()->setCartographic(Cartographic::fromDegrees(114.054494, 22.540745, 50));

    scene->addEntity(entity);

    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
    QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
        if (key == Qt::Key_Left) {
            auto cart = entity->transform()->cartographic();
            cart.longitude -= Math::toRadians(0.01);
            entity->transform()->setCartographic(cart);
        }
        if (key == Qt::Key_Right) {
            auto cart = entity->transform()->cartographic();
            cart.longitude += Math::toRadians(0.01);
            entity->transform()->setCartographic(cart);
        }
        if (key == Qt::Key_Up) {
            auto cart = entity->transform()->cartographic();
            cart.latitude += Math::toRadians(0.01);
            entity->transform()->setCartographic(cart);
        }
        if (key == Qt::Key_Down) {
            auto cart = entity->transform()->cartographic();
            cart.latitude -= Math::toRadians(0.01);
            entity->transform()->setCartographic(cart);
        }
   });
}

void createFire(LiScene *scene)
{
    LiParticleSystem *particleSystem = new LiParticleSystem();
    particleSystem->setDebugMode(false);

    // fire 1
    if (1)
    {
        LiParticleEmitter *emitter = new LiParticleEmitter(particleSystem);
        emitter->setShapeType(LiParticleEmitter::Ellipse);
        emitter->setShapeSize(Vector2(200, 100));
        emitter->setFillShape(false);
        emitter->setParticlesPerSecond(30);
        emitter->setParticleDuration(3000); // 3 seconds
        emitter->setParticleSize(Vector2(12,12));
//        emitter->setParticleEndSize(Vector2(2,2));
//        emitter->setParticleSizeVariation(Vector2(4,4));
        emitter->setOffset(Vector3(100, 100, 30));

        // velocity
        LiPointDirection *vec = new LiPointDirection(emitter);
        vec->setXVariation(1);
        vec->setYVariation(1);
        emitter->setVelocity(vec);

        // acceleration
        LiPointDirection *acc = new LiPointDirection(emitter);
        acc->setX(8);
        acc->setXVariation(1);
        acc->setYVariation(1);
        emitter->setAcceleration(acc);

        particleSystem->registerParticleEmitter(emitter);

//        LiGravityAffector *gravity = new LiGravityAffector();
//        gravity->setMagnitude(20);
//        particleSystem->registerParticleAffector(gravity);
    }

    // fire 2
    if (0)
    {
        LiParticleEmitter *emitter = new LiParticleEmitter(particleSystem);
        emitter->setShapeType(LiParticleEmitter::Rectangle);
        emitter->setShapeSize(Vector2(10, 10));
        emitter->setFillShape(true);
        emitter->setParticlesPerSecond(50);
        emitter->setParticleDuration(3500); // 3.5 seconds
//        emitter->setParticleSize(12);
//        emitter->setParticleEndSize(2);
//        emitter->setParticleSizeVariation(4);
        emitter->setOffset(Vector3(-100, 100, 0));

        // velocity
        LiPointDirection *vec = new LiPointDirection(emitter);
        vec->setXVariation(1);
        vec->setYVariation(1);
        emitter->setVelocity(vec);

        // acceleration
        LiPointDirection *acc = new LiPointDirection(emitter);
        acc->setZ(8);
        acc->setXVariation(1);
        acc->setYVariation(1);
        emitter->setAcceleration(acc);

        particleSystem->registerParticleEmitter(emitter);
    }

    // fire 3
    if (0)
    {
        LiParticleEmitter *emitter = new LiParticleEmitter(particleSystem);
        emitter->setShapeType(LiParticleEmitter::Line);
        emitter->setShapeSize(Vector2(200, 100));
        emitter->setFillShape(false);
        emitter->setParticlesPerSecond(200);
        emitter->setParticleDuration(3500); // 3.5 seconds
//        emitter->setParticleSize(12);
//        emitter->setParticleEndSize(2);
//        emitter->setParticleSizeVariation(4);
        emitter->setOffset(Vector3(-100, -100, 0));

        // velocity
        LiPointDirection *vec = new LiPointDirection(emitter);
        vec->setXVariation(1);
        vec->setYVariation(1);
        emitter->setVelocity(vec);

        // acceleration
        LiPointDirection *acc = new LiPointDirection(emitter);
        acc->setZ(8);
        acc->setXVariation(1);
        acc->setYVariation(1);
        emitter->setAcceleration(acc);

        particleSystem->registerParticleEmitter(emitter);
    }

    LiImageParticleRenderer *renderer = new LiImageParticleRenderer(particleSystem);
    renderer->setColor(QColor::fromRgba(0x8fff400f));
    renderer->setColorVariation(0.1);
//    renderer->setAlignedAxis(Vector3::xAxis);
    particleSystem->registerParticleRenderer(renderer);

    LiEntity *entity = new LiEntity();
    entity->transform()->setCartographic(Cartographic::fromDegrees(114.054494, 22.540745, 0));
    entity->addComponent(particleSystem);
    scene->addEntity(entity);

    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
    QObject::connect(input, &LiInputSystem::keyDown, [particleSystem](int key) {
        if (key == Qt::Key_R) {
            particleSystem->reset();
        }
    });
}

void createHeatmap(LiScene *scene)
{
    QgsVectorLayer *vectorLayer = new QgsVectorLayer(QString::fromLocal8Bit("D:/work/LiEngine/x64/debug/data/shp/模型点位.shp"), "layer");

    LiHeatmapLayer *heatmapLayer = new LiHeatmapLayer();
    heatmapLayer->load(vectorLayer);

    LiEntity *entity = new LiEntity();
    entity->addComponent(heatmapLayer);
    scene->addEntity(entity);
}

#include "qgslayerdefinition.h"
#include "qgslayertreegroup.h"
#include "qgslayertreelayer.h"
#include "qgslayertree.h"

void createGisImageryProvider(LiScene *scene)
{
    GisImageryProvider *provider = new GisImageryProvider();
    LiEntity *entity = new LiEntity;
    entity->addComponent(provider);
    scene->addEntity(entity);

    QString errorMsg;
    QgsProject *project = QgsProject::instance();
    QgsLayerTree *layerTree = project->layerTreeRoot();
    QgsLayerDefinition::loadLayerDefinition("D:/Temp/shp/china.qlr", project, layerTree, errorMsg);
    if (errorMsg.size())
        qDebug() << errorMsg;
    const auto layers = layerTree->findLayers();
    for (auto layer : layers)
        provider->addLayer(layer->layer());
}

void createLights(LiScene *scene)
{
    double space = 300;

    LiEntity *parent = new LiEntity();

    for (int y = -10; y < 10; ++y)
    {
        for (int x = -10; x < 10; ++x)
        {
            Vector3 pos(x * space, y * space, 100);

            LiLight *light = new LiLight(LiLight::Point);
            light->setRange(250);
            light->setColor(QColor(200, 100, 20));
            light->setIntensity(2.5f);

            LiEntity *ent = new LiEntity(parent);
            ent->transform()->setPosition(pos);
            ent->addComponent(light);
        }
    }

    parent->transform()->setCartographic(Cartographic::fromDegrees(114.054494, 22.540745, 0));
    scene->addEntity(parent);
}

void createClipPlane(LiScene *scene)
{
    Cartesian3 cartesian = Cartesian3::fromDegrees(114.054494, 22.540745, 50);
    Vector3 normal = Ellipsoid::WGS84()->geodeticSurfaceNormal(cartesian);

    // clip plane 0
    scene->setClipPlane(Plane(cartesian, -normal), 0);
    scene->enableClipPlane(true, 0);

    // clip plane 1
    Quaternion q = Quaternion::fromAxisAndAngle(1, 0, 0, 90);
    normal = q.toRotationMatrix() * normal;
    scene->setClipPlane(Plane(cartesian, normal), 1);
    scene->enableClipPlane(true, 1);

    // up to 8 clip planes
    // ...
}

void createClipVolume(LiScene *scene)
{
    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();

    // Ctrl+鼠标点击会创建裁切体
    QObject::connect(input, &LiInputSystem::leftButtonDown, [=] {
        if (input->getKey(Qt::Key_Control)) {
            auto p = input->mousePosition();
            Ray ray = scene->mainCamera()->screenPointToRay(p.x(), p.y());
            LiRaycastHit hit;

            if (scene->raycast(ray, &hit)) {
                LiClipVolume *clipVolume = new LiClipVolume();
                clipVolume->setSize(Vector3(1000, 1000, 1000)); // 设置裁切体的长宽高
                clipVolume->setShowDebugVolume(true); // 显示裁切体的包围盒
//                clipVolume->setClipFlag(LiClipVolume::ClipGlobe);

                LiEntity *entity = new LiEntity();
                entity->addComponent(clipVolume);
                scene->addEntity(entity);

                // 利用transform组件设置裁切体的位置和旋转角度
                entity->transform()->setCartographic(Cartographic::fromCartesian(hit.point()));
            }
        }
    });
}

void createWaterMaterial(LiScene *scene)
{
    LiMaterial *mat = new LiMaterial();
    mat->setShadingModel(LiMaterial::Water);

    LiPlaneGeometry *geometry = new LiPlaneGeometry();
    geometry->setWidth(1000);
    geometry->setHeight(1000);
    geometry->setResolution(QSize(10, 10));
    geometry->create();

    LiGeometryRenderer *renderer = new LiGeometryRenderer();
    renderer->setGeometry(geometry);
    renderer->setMaterial(mat);

    LiFeature *feature = new LiFeature;
    feature->setProperty("Who are you?", QString("I'm water."));
    feature->setProperty("How are you?", QString("I'm fine."));
    feature->setProperty("Where are you?", QString("I'm working."));
    renderer->setFeature(feature);

    LiEntity *entity = new LiEntity();
    entity->addComponent(renderer);
    entity->transform()->setCartographic(Cartographic::fromDegrees(114.054494, 22.540745, 5));

    scene->addEntity(entity);
}

static void setTime(int &hour, int &minute)
{
    if (minute < 0) {
        minute += 60;
        hour--;
    }

    hour += minute / 60;
    minute = minute % 60;

    if (hour < 0) {
        hour += 24;
    }
    if (hour >= 24) {
        hour -= 24;
    }

    qDebug() << "hour:" << hour << "minute:" << minute;
}

void controlTime()
{
    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();

    QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
        int n = input->getKey(Qt::Key_Shift) ? 30 : 5;
        if (key == Qt::Key_F5) {
            LiTimeSystem *ts = GlobalViewer()->engine()->timeSystem();
            QDateTime dt = ts->dateTime();
            if (!dt.isValid())
            {
                dt = QDateTime::currentDateTime();
            }
            QTime t = dt.time();
            int h = t.hour();
            int m = t.minute() - n;
            setTime(h, m);
            t = QTime(h, m);
            dt = QDateTime(dt.date(), t);
            ts->setDateTime(dt);
        }
        if (key == Qt::Key_F6) {
            LiTimeSystem *ts = GlobalViewer()->engine()->timeSystem();
            QDateTime dt = ts->dateTime();
            if (!dt.isValid())
            {
                dt = QDateTime::currentDateTime();
            }
            QTime t = dt.time();
            int h = t.hour();
            int m = t.minute() + n;
            setTime(h, m);
            t = QTime(h, m);
            dt = QDateTime(dt.date(), t);
            ts->setDateTime(dt);
        }
    });
}

#include "lipluginimageryprovider.h"

void loadWMS()
{
    // arcgis server
    if (1)
    {
//        auto provider = new LiPluginImageryProvider("arcgismapserver", "crs='EPSG:3857' format='JPG' layer='0' url='http://services.arcgisonline.com/ArcGIS/rest/services/Canvas/World_Dark_Gray_Base/MapServer'");
        auto provider = new LiPluginImageryProvider("arcgismapserver", "crs='EPSG:3857' format='JPG' layer='0' url='https://services.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer'");
        auto imageryLayer = new ImageryLayer(provider);
//        imageryLayer->setAlpha(0.5f);
        GlobalViewer()->scene()->globe()->addImageryLayer(imageryLayer);
    }

    // OpenStreetMap
    if (0)
    {
        auto provider = new LiPluginImageryProvider("wms", "type=xyz&url=http://a.tile.openstreetmap.org/%7Bz%7D/%7Bx%7D/%7By%7D.png&zmax=19&zmin=0");
        auto imageryLayer = new ImageryLayer(provider);
        GlobalViewer()->scene()->globe()->addImageryLayer(imageryLayer);
    }

    // wms server
    if (1)
    {
        auto provider = new LiPluginImageryProvider("wms", "crs=EPSG:4326&dpiMode=all&format=image/png&layers=topp:states&styles=&url=https://demo.geo-solutions.it/geoserver/wms/");
        auto imageryLayer = new ImageryLayer(provider);
        GlobalViewer()->scene()->globe()->addImageryLayer(imageryLayer);
    }

    // wmts server
    if (0)
    {
        auto provider = new LiPluginImageryProvider("wms", "contextualWMSLegend=0&crs=EPSG:3857&dpiMode=7&featureCount=10&format=image/png&layers=geolandbasemap&styles=normal&tileMatrixSet=google3857&url=https://maps.wien.gv.at/basemap/1.0.0/WMTSCapabilities.xml");
        provider->setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36");
        auto imageryLayer = new ImageryLayer(provider);
        GlobalViewer()->scene()->globe()->addImageryLayer(imageryLayer);
    }
    if (0)
    {
        auto provider = new LiPluginImageryProvider("wms", "contextualWMSLegend=0&crs=EPSG:4490&dpiMode=7&featureCount=10&format=image/jpgpng&layers=SZIMAGE_SZAVI201111_50ZW2K&styles=default&tileMatrixSet=default&url=http://10.1.3.131:6080/arcgis/rest/services/SZIMAGE/SZAVI201111_50ZW2K/ImageServer/WMTS/1.0.0/WMTSCapabilities.xml");
//        provider->setUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36");
        auto imageryLayer = new ImageryLayer(provider);
        GlobalViewer()->scene()->globe()->addImageryLayer(imageryLayer);
    }

    // arcgis server
    if (1)
    {
        auto provider = new LiPluginImageryProvider("arcgismapserver", "crs='EPSG:4490' format='JPG' layer='0' url='http://ag.szgeoinfo.com/arcgis/rest/services/szimage/MapServer'");
        auto imageryLayer = new ImageryLayer(provider);
//        imageryLayer->setAlpha(0.5f);
//        imageryLayer->setBrightness(0.5f);
//        imageryLayer->setContrast(0.8f);
//        imageryLayer->setHue(0.8);
//        imageryLayer->setSaturation(0.7f);
//        imageryLayer->setGamma(1.5f);
        GlobalViewer()->scene()->globe()->addImageryLayer(imageryLayer);

        LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
        QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
            if (key == Qt::Key_F1) {
                float alpha = std::max(0.f, imageryLayer->alpha()-0.1f);
                imageryLayer->setAlpha(alpha);
            }
            if (key == Qt::Key_F2) {
                float alpha = std::min(1.f, imageryLayer->alpha()+0.1f);
                imageryLayer->setAlpha(alpha);
            }
        });
    }
}

#include "pmtscapabilities.h"

void loadPMTS()
{
    QString url("http://3ddatapublishgataway.pnr.test/freeserver-pmts/services/share/f1d216a3-4c09-4ba0-9f75-4f0725e732dc/pmts/1.1.0/PMTSCapabilities.json?accesskey=083e7233-a73e-4f68-a7da-e7252d5913aa");

    PMTSCapabilities *pmts = new PMTSCapabilities(url);
    observe(pmts->readyPromise()).subscribe([=] {
        const auto modelUrls = pmts->modelUrls();
        for (const auto &url : modelUrls) {
//            qDebug() << url;
            auto tileset = new Li3DTileset(url);
            tileset->setClampedTerrain(false);
            auto entity = new LiEntity();
            entity->addComponent(tileset);
            GlobalViewer()->scene()->addEntity(entity);
        }
        delete pmts;
    }, [=] {
        delete pmts;
        qDebug() << "Failed to load:" << url;
    });
}

void flattenTerrain()
{
    QVector<Vector3> points;
    points << Vector3(-2.40054e+06, 5.38009e+06, 2.43593e+06)
           << Vector3(-2.40191e+06, 5.38055e+06, 2.43345e+06)
           << Vector3(-2.40035e+06, 5.38154e+06, 2.43278e+06)
           << Vector3(-2.39851e+06, 5.38116e+06, 2.43558e+06);

    QVector<Vector3> points2;
    points2 << Vector3(-2.40183e+06, 5.38015e+06, 2.43432e+06)
            << Vector3(-2.40262e+06, 5.37885e+06, 2.43638e+06)
            << Vector3(-2.40417e+06, 5.37882e+06, 2.43494e+06)
            << Vector3(-2.40529e+06, 5.3784e+06, 2.43477e+06)
            << Vector3(-2.40488e+06, 5.37923e+06, 2.43334e+06)
            << Vector3(-2.40354e+06, 5.37956e+06, 2.43393e+06);

    auto mask = new LiFlattenMask;
    mask->setPoints(points);
    mask->setMaskHeight(30);
    mask->setShowDebugOutline(true);

    auto mask2 = new LiFlattenMask;
    mask2->setPoints(points2);
    mask2->setMaskHeight(-78);
    mask2->setShowDebugOutline(true);

    LiInputSystem *input = GlobalViewer()->engine()->inputSystem();
    QObject::connect(input, &LiInputSystem::keyDown, [=](int key) {
        if (key == Qt::Key_PageDown) {
            mask->setMaskHeight(mask->maskHeight() - 10);
        }
        if (key == Qt::Key_PageUp) {
            mask->setMaskHeight(mask->maskHeight() + 10);
        }
        if (key == Qt::Key_F1) {
            mask->setEnabled(!mask->isEnabled());
        }
        if (key == Qt::Key_F2) {
            mask2->setEnabled(!mask2->isEnabled());
        }
    });

    GlobalViewer()->scene()->globe()->addFlattenMask(mask);
    GlobalViewer()->scene()->globe()->addFlattenMask(mask2);
}

void load3DTileset(const QString &uri)
{
    Li3DTileset *tileset;
    LiEntity *entity;

    if (1)
    {
        tileset = new Li3DTileset(uri);
        tileset->setClampedTerrain(false); // 贴地模式 (默认为true)
//        tileset->setDebugBoundingVolume(true);
        entity = new LiEntity;
        entity->addComponent(tileset);
        GlobalViewer()->scene()->addEntity(entity);
        flytoTileset(tileset);
    }
}
