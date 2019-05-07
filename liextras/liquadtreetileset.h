#ifndef LIQUADTREETILESET_H
#define LIQUADTREETILESET_H

#include "liextrasglobal.h"
#include "li3dtileset.h"
#include "cartographic.h"
#include "boundingsphere.h"
#include "future.h"
#include "asyncfuture.h"
#include <QDomDocument>
#include <QDomNode>

class LIEXTRAS_EXPORT LiQuadtreeTileset : public Li3DTileset
{
    Q_OBJECT
public:
    LiQuadtreeTileset(const QString &url,
                      Qt::Axis upAxis = Qt::YAxis,
                      double geometricError = 64.0,
                      LiNode *parent = nullptr);

    Future load(const QUrl &url);
    QJsonObject json() const { return m_json; }

private:
    QFuture<QVariant> loadNode(const QUrl &url);
    QJsonObject createNodeJson(const QDomElement &element, const QUrl &baseUrl, int level, const Matrix4 &parentTransform);
    QJsonObject createBoundingVolume(const BoundingSphere &sphere);

    Qt::Axis m_upAxis;
    double m_geometricError = 64.0;
    BoundingSphere m_boundingSphere;
    QJsonObject m_json;
    QJsonObject m_rootJson;
    QJsonArray m_childrenJson;
    QVector<Deferred<QVariant>> m_defers;
    Deferred<void> m_readyPromise;
    Matrix4 m_rootTransform;
    Matrix4 m_rootInverseTransform;
};

#endif // LIQUADTREETILESET_H
