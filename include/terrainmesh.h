#ifndef TERRAINMESH_H
#define TERRAINMESH_H

#include "licore_global.h"
#include "linodeid.h"
#include "cartesian3.h"
#include "boundingsphere.h"
#include "orientedboundingbox.h"
#include "boundingvolume.h"

class TerrainEncoding;

class LICORE_EXPORT TerrainMesh
{
public:
    TerrainMesh();
    ~TerrainMesh();

    Cartesian3 decodePosition(int index) const;
    double decodeHeight(int index) const;
    Cartesian2 decodeTexCoords(int index) const;

    int vertexCount() const { return vertices.size() / vertexStrideBytes; }
    int indexCount() const { return indices.size() / indexStrideBytes; }

public:
    Cartesian3 center;
    double minimumHeight = 0.f;
    double maximumHeight = 0.f;
    QByteArray vertices;
    int vertexStrideBytes = 0;
    QByteArray indices;
    int indexStrideBytes = 0;
    int indexCountWithoutSkirts = 0;
    int primitiveType = -1;
    BoundingVolume boundingVolume;
    Cartesian3 occludeePointInScaledSpace;
    QSharedPointer<TerrainEncoding> encoding;
    double exaggeration = 1.0;
};

#endif // TERRAINMESH_H
