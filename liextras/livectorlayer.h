#ifndef LIVECTORLAYER_H
#define LIVECTORLAYER_H

#include "liextrasglobal.h"
#include "cartesian2.h"
#include "cartographic.h"
#include "rectangle.h"
#include <qgsvectorlayer.h>

class LIEXTRAS_EXPORT LiVectorLayer : public QObject
{
    Q_OBJECT
public:
    enum State
    {
        UNLOADED = 0,
        LOADING = 1,
        LOADED = 2,
        INVALID = 3
    };

    explicit LiVectorLayer(QgsVectorLayer *layer, QObject *parent = nullptr);
    virtual ~LiVectorLayer();

    State state() const { return _state; }
    QgsVectorLayer *vectorLayer() const { return _vectorLayer; }
    LiRectangle rectangle() const { return _rectangle; }
    QgsRectangle extent() const { return _extent; }

    bool startStreaming();
    void stopStreaming();

    void setAttributeList(const QStringList &attrList) { _attributeList = attrList; }
    QStringList attributeList() const { return _attributeList; }

    QgsRectangle desiredExtent() const { return _desiredExtent; }
    void setDesiredExtent(const QgsRectangle &extent) { _desiredExtent = extent; }

signals:
    void featureLoaded(const QgsFeature &feature);
    void completed();

protected:
    State _state;
    QAtomicInt _streaming;
    QAtomicInt _running;
    QgsVectorLayer *_vectorLayer;
    QgsRectangle _extent;
    LiRectangle _rectangle;
    QStringList _attributeList;
    QgsRectangle _desiredExtent;
};

#endif // LIVECTORLAYER_H
