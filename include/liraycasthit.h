#ifndef LIRAYCASTHIT_H
#define LIRAYCASTHIT_H

#include "licore_global.h"
#include "vector3.h"

class LiEntity;
class LiScene;
class LiRaycastHitPrivate;

class LICORE_EXPORT LiRaycastHit : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double distance READ distance FINAL)
    Q_PROPERTY(Vector3 point READ point FINAL)
    Q_PROPERTY(Vector3 normal READ normal FINAL)
    Q_PROPERTY(LiEntity* entity READ entity FINAL)
public:
    explicit LiRaycastHit(QObject *parent = nullptr);

    double distance() const;
    void setDistance(double distance);

    Vector3 point() const;
    void setPoint(const Vector3 &point);

    Vector3 normal() const;
    void setNormal(const Vector3 &normal);

    LiEntity *entity() const;
    void setEntity(LiEntity *entity);

private:
    QSharedPointer<LiRaycastHitPrivate> d;
    friend class LiScene;

//    barycentricCoordinate	The barycentric coordinate of the triangle we hit.
//    collider	The Collider that was hit.
//    distance	The distance from the ray's origin to the impact point.
//    lightmapCoord	The uv lightmap coordinate at the impact point.
//    normal	The normal of the surface the ray hit.
//    point	The impact point in world space where the ray hit the collider.
//    rigidbody	The Rigidbody of the collider that was hit. If the collider is not attached to a rigidbody then it is null.
//    textureCoord	The uv texture coordinate at the impact point.
//    textureCoord2	The secondary uv texture coordinate at the impact point.
//    transform	The Transform of the rigidbody or collider that was hit.
//    triangleIndex	The index of the triangle that was hit.
};

#endif // LIRAYCASTHIT_H
