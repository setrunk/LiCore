#include "liquadtreetileset.h"
#include "lifilesystem.h"
#include "lientity.h"
#include "litransform.h"
#include "transformhelper.h"
#include "ellipsoid.h"
#include "transforms.h"
#include "liutils.h"
#include <qgscoordinatereferencesystem.h>

LiQuadtreeTileset::LiQuadtreeTileset(const QString &url,
                                     Qt::Axis upAxis,
                                     double geometricError,
                                     LiNode *parent)
    : Li3DTileset(parent)
    , m_upAxis(upAxis)
    , m_geometricError(geometricError)
{
    _url = url;
    _baseUrl = getBaseUrl(_url);

    auto promise = load(url);
    if (!promise.isCanceled())
    {
        observe(promise).subscribe([=]() {
            initialize(m_json);
//            QJsonDocument doc(m_json);
//            QFile f("d:/tileset.json");
//            f.open(QFile::WriteOnly);
//            f.write(doc.toJson());
//            f.close();
        });
    }
}

Future LiQuadtreeTileset::load(const QUrl &url)
{
    auto promise = LiFileSystem::readFile(url);
    if (promise.isCanceled())
        return Future();

    // asset
    {
        QJsonObject obj;
        obj["version"] = 0.0;
        obj["gltfUpAxis"] = "Z";
        m_json["asset"] = obj;
    }

    // geometricError
    {
        m_json["geometricError"] = m_geometricError;
    }

    // root
    {
        m_rootJson["geometricError"] = m_geometricError;
        m_rootJson["refine"] = "REPLACE";
    }

    observe(promise).subscribe([=](QByteArray buffer) {
        QDomDocument doc;
        QDomElement e;
        if (doc.setContent(QString::fromUtf8(buffer))) {
            QDomElement docElem = doc.documentElement();

            e = docElem.firstChildElement("SRS");
            if (!e.isNull()) {
                QgsCoordinateReferenceSystem crs;
                crs.createFromOgcWmsCrs(e.text());
                if (crs.isValid()) {
                    e = docElem.firstChildElement("Local");
                    if (!e.isNull()) {
                        double x = e.attribute("x").toDouble();
                        double y = e.attribute("y").toDouble();
                        double z = e.attribute("z").toDouble();
                        Cartographic cartographic = TransformHelper::instance()->toWgs84(x, y, &crs);
                        cartographic.height = z;

                        Cartesian3 point = Ellipsoid::WGS84()->cartographicToCartesian(cartographic);
                        m_rootTransform = Transforms::eastNorthUpToFixedFrame(point);
                        m_rootInverseTransform = m_rootTransform.inverted();

                        m_rootJson["transform"] = matrix4ToJsonArr(m_rootTransform);
                    }
                }
            }

            QVector<QFuture<QVariant>> futures;

            e = docElem.firstChildElement("Tile");
            while (!e.isNull()) {
                QString path = e.attribute("path");
                QUrl url = resolvedQueryUrl(_baseUrl, QUrl(path));
                auto nodeFuture = loadNode(url);
                if (!nodeFuture.isCanceled()) {
                    observe(nodeFuture).subscribe([=](QVariant data) {
                        QJsonObject nodeJson = data.toJsonObject();
                        if (!nodeJson.isEmpty()) {
                            m_childrenJson.append(nodeJson);
                        }
                    });
                    futures.append(nodeFuture);
                }
                e = e.nextSiblingElement("Tile");
            }

            if (futures.size())
            {
                auto combined = combine();
                for (const auto &f : futures)
                {
                    combined << f;
                }

                observe(combined.future()).subscribe([=]() {
                    m_rootJson["children"] = m_childrenJson;
                    m_rootJson["boundingVolume"] = createBoundingVolume(m_boundingSphere);
                    m_json["root"] = m_rootJson;
                    m_readyPromise.complete();
                });
            }
            else
            {
                m_rootJson["children"] = m_childrenJson;
                m_rootJson["boundingVolume"] = createBoundingVolume(m_boundingSphere);
                m_json["root"] = m_rootJson;
                m_readyPromise.complete();
            }
        }
        else
        {
            m_readyPromise.cancel();
        }
    });

    return m_readyPromise.future();
}

QFuture<QVariant> LiQuadtreeTileset::loadNode(const QUrl &url)
{
    auto promise = LiFileSystem::readFile(url);
    if (promise.isCanceled())
        return QFuture<QVariant>();

    int index = m_defers.size();
    Deferred<QVariant> defer;
    m_defers.append(defer);

    observe(promise).subscribe([=](QByteArray buffer) {
        QDomDocument doc;
        QDomElement e;
        if (doc.setContent(QString::fromUtf8(buffer))) {
            QDomElement docElem = doc.documentElement();
            e = docElem.firstChildElement("Tile");
            if (!e.isNull()) {
                QUrl baseUrl = getBaseUrl(url);
                QJsonObject o = createNodeJson(e, baseUrl, 0, m_rootTransform);
                m_defers[index].complete(o);
            } else {
                m_defers[index].cancel();
            }
        }
    });

    return m_defers[index].future();
}

QJsonObject LiQuadtreeTileset::createNodeJson(const QDomElement &element, const QUrl &baseUrl, int level, const Matrix4 &parentTransform)
{
    QJsonObject json;
    json["refine"] = "REPLACE";

    QDomElement e;

    e = element.firstChildElement("MinRange");
    if (!e.isNull()) {
//        json["geometricError"] = e.text().toDouble();
        json["geometricError"] = m_geometricError * (1.0 / (1<<level));
    }

    double radius = 0.0;
    e = element.firstChildElement("Radius");
    if (!e.isNull()) {
        radius = e.text().toDouble();
    }

    Vector3 center;
    e = element.firstChildElement("Center");
    if (!e.isNull()) {
        center = Vector3(e.attribute("x").toDouble(),
                         e.attribute("y").toDouble(),
                         e.attribute("z").toDouble());
    }

    Matrix4 transform = m_rootTransform * Matrix4::fromTranslation(center);
    Matrix4 localTransform = parentTransform.inverted() * transform;
    json["transform"] = matrix4ToJsonArr(localTransform);

    m_boundingSphere.merge(BoundingSphere(center, radius));

    QJsonArray sphere;
    sphere.append(0.0);
    sphere.append(0.0);
    sphere.append(0.0);
//    sphere.append(center.x());
//    sphere.append(center.y());
//    sphere.append(center.z());
    sphere.append(radius);

    QJsonObject boundingVolume;
    boundingVolume["sphere"] = sphere;

    json["boundingVolume"] = boundingVolume;

    e = element.firstChildElement("ModelPath");
    if (!e.isNull()) {
        QUrl url = resolvedQueryUrl(baseUrl, QUrl(e.text()));
        QString path = url.toString();
        path.remove(0, _baseUrl.toString().length());
        QJsonObject content;
        content["url"] = path;
        json["content"] = content;
    }

    QJsonArray children;

    e = element.firstChildElement("Node");
    while (!e.isNull()) {
        QJsonObject c = createNodeJson(e, baseUrl, level+1, transform);
        children.append(c);
        e = e.nextSiblingElement("Node");
    }

    if (children.size())
    {
        json["children"] = children;
    }

    return json;
}

QJsonObject LiQuadtreeTileset::createBoundingVolume(const BoundingSphere &sphere)
{
    QJsonArray a;
    a.append(sphere.center.x());
    a.append(sphere.center.y());
    a.append(sphere.center.z());
    a.append(sphere.radius);

    QJsonObject o;
    o["sphere"] = a;

    return o;
}
