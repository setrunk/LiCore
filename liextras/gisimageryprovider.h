#ifndef GISIMAGERYPROVIDER_H
#define GISIMAGERYPROVIDER_H

#include "liextrasglobal.h"
#include "rectangle.h"
#include "libehavior.h"

class QgsMapLayer;
class LiTexture;
class QuadtreeTile;
class LiWorkerThread;

class LIEXTRAS_EXPORT GisImageryProvider : public LiBehavior
{
    Q_OBJECT
public:
    explicit GisImageryProvider(LiNode *parent = nullptr);

    void addLayer(QgsMapLayer *layer);
    void removeLayer(QgsMapLayer *layer);

    void update();

private:
    enum State
    {
        Start,
        Loading,
        Ready,
        Removed
    };

    struct TileData
    {
        ~TileData();
        State state = Start;
        quint64 key = 0;
        LiTexture *texture = nullptr;
        QuadtreeTile *tile = nullptr;
        LiRectangle rectangle;
        bool emptyImage = false;
    };
    QHash<quint64, TileData*> _dataHash;

    LiWorkerThread *_thread = nullptr;
    LiRectangle _extent;
    QList<QgsMapLayer*> _layers;
    QHash<QgsMapLayer*, QMetaObject::Connection> _connections;

    void requestImage(TileData *tileData);
    void repaint(const LiRectangle &extent, bool add);
};


#endif // GISIMAGERYPROVIDER_H
