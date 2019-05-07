#ifndef CESIUM3DTILECONTENT_H
#define CESIUM3DTILECONTENT_H

#include "licore_global.h"
#include "asyncfuture.h"
#include "future.h"
#include "matrix4.h"
#include "cartographic.h"

class Li3DTile;
class Li3DTileset;
class Li3DTileFeature;
class Li3DTileBatchTable;
class Li3DTileFeatureTable;
class LiEntity;
class LiScene;

class LICORE_EXPORT Li3DTileContent
{
public:
    Li3DTileContent(Li3DTileset *tileset,
                    Li3DTile *tile,
                    const QUrl &url = QUrl(),
                    const QByteArray &arrayBuffer = QByteArray(),
                    int byteOffset = 0);

    virtual ~Li3DTileContent();

    QUrl url() const { return _url; }
    Li3DTile *tile() const { return _tile; }
    Li3DTileBatchTable *batchTable() const { return _batchTable; }
    Future readyPromise() const { return _readyPromise.future(); }
    Li3DTileFeature *getFeature(int batchId);

    bool featurePropertiesDirty() const { return _featurePropertiesDirty; }
    void setFeaturePropertiesDirty(bool value) { _featurePropertiesDirty = value; }

    int addRef();
    void release();
    void contentLoaded();
    void setAltitude(double altitude);
    void createPickTexture(LiScene *scene);

    virtual void update();
    virtual void destroy();
    virtual void updateTransform();

    virtual LiEntity *model() { return _model; }
    virtual int featuresLength() const { return _featuresLength; }
    virtual int pointsLength() const { return _pointsLength; }
    virtual int trianglesLength() const { return _trianglesLength; }
    virtual int geometryByteLength() const { return _geometryByteLength; }
    virtual int texturesByteLength() const { return _texturesByteLength; }
    virtual int batchTableByteLength() const { return _batchTableByteLength; }
    virtual QVector<Li3DTileContent*> innerContents() const { return QVector<Li3DTileContent*>(); }

protected:
    void createFeatures();

    QBasicAtomicInt _ref;
    QUrl _url;
    Li3DTileset *_tileset;
    Li3DTile *_tile;
    LiEntity *_model;
    Li3DTileBatchTable *_batchTable;
    QVector<Li3DTileFeature*> _features;
    Deferred<void> _readyPromise;
    Cartographic _centerCartographic;
    Vector3 _centerPosition;
    Matrix4 _modelMatrix;
    int _featuresLength = 0;
    int _pointsLength = 0;
    int _trianglesLength = 0;
    int _geometryByteLength = 0;
    int _texturesByteLength = 0;
    int _batchTableByteLength = 0;
    bool _isDestroyed = false;
    bool _featurePropertiesDirty = false;
};

#endif // CESIUM3DTILECONTENT_H
