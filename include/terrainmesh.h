#ifndef TERRAINMESH_H
#define TERRAINMESH_H

#include "licore_global.h"
#include "linodeid.h"
#include "cartesian3.h"
#include "boundingsphere.h"
#include "orientedboundingbox.h"
#include "boundingvolume.h"

class TerrainEncoding;
class LiFlattenMask;
class LiBuffer;

class LICORE_EXPORT TerrainMesh
{
public:
    TerrainMesh();
    ~TerrainMesh();

    Cartesian3 decodePosition(int index) const;
    double decodeHeight(int index) const;
    Cartesian2 decodeTexCoords(int index) const;

    int vertexCount() const { return vertexData.size() / vertexStrideBytes; }
    int indexCount() const { return indexData.size() / indexStrideBytes; }

    void restoreLodedData();
    QFuture<void> flattenMesh(const LiRectangle &rectangle, const QVector<LiFlattenMask *> &flattenMasks);
    void onFlattenMaskHeightChanged(const LiRectangle &rectangle, LiFlattenMask *mask);

public:
    struct FlattenMaskData
    {
        double height;
        LiRectangle extent;
        QPainterPath normalizedPath;
        QPolygonF normalizedPoints;
        QVector<int> insideVertices;
    };
    typedef QSharedPointer<FlattenMaskData> FlattenMaskDataPtr;

    struct FlattenParameters
    {
        LiRectangle rectangle;
        QByteArray vertexData;
        QByteArray indexData;
        int vertexCountWithoutSkirts = 0;
        int indexCountWithoutSkirts = 0;
        double minimumHeight = 0;
        double maximumHeight = 0;
        QSharedPointer<TerrainEncoding> encoding;
        QVector<FlattenMaskDataPtr> flattenMasks;
    };

    struct MeshData
    {
        QByteArray vertexData;
        QByteArray indexData;
        int vertexCountWithoutSkirts = 0;
        int indexCountWithoutSkirts = 0;
        BoundingVolume boundingVolume;
    };
    MeshData loadedData;

//    MeshData *doFlatten(const LiRectangle &rectangle, const QVector<FlattenMaskDataPtr> &flattenMasks);
//    void addSkirt(float *vbuffer,
//                  int &vertexBufferIndex,
//                  quint16 *ibuffer,
//                  int &indexBufferIndex,
//                  const QVector<quint16> &edgeVertices,
//                  const QVector<QPointF> &uvs,
//                  const QVector<double> &heights,
//                  const LiRectangle &rectangle,
//                  double skirtLength,
//                  bool isWestOrNorthEdge,
//                  double southMercatorY,
//                  double oneOverMercatorHeight);

    void saveLoadedData()
    {
        loadedData.vertexData = vertexData;
        loadedData.vertexCountWithoutSkirts = vertexCountWithoutSkirts;
        loadedData.indexData = indexData;
        loadedData.indexCountWithoutSkirts = indexCountWithoutSkirts;
        loadedData.boundingVolume = boundingVolume;
    }

    Cartesian3 center;
    double minimumHeight = 0.f;
    double maximumHeight = 0.f;
    QByteArray vertexData;
    int vertexStrideBytes = 0;
    int vertexCountWithoutSkirts = 0;
    QByteArray indexData;
    int indexStrideBytes = 0;
    int indexCountWithoutSkirts = 0;
    int primitiveType = -1;
    BoundingVolume boundingVolume;
    Cartesian3 occludeePointInScaledSpace;
    QSharedPointer<TerrainEncoding> encoding;
    double exaggeration = 1.0;
    double westSkirtHeight = 0;
    double eastSkirtHeight = 0;
    double southSkirtHeight = 0;
    double northSkirtHeight = 0;
    LiBuffer *vertexBuffer = nullptr;
    LiBuffer *indexBuffer = nullptr;
    bool working = false;
    bool destroyed = false;
    int maskId = 0;
    QHash<LiFlattenMask *, FlattenMaskDataPtr> maskDataHash;
};

#endif // TERRAINMESH_H
