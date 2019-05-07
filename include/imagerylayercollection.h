#ifndef IMAGERYLAYERCOLLECTION_H
#define IMAGERYLAYERCOLLECTION_H

#include "licore_global.h"

class Imagery;
class ImageryLayer;
class ImageryProvider;

/**
 * @brief
 * ImageryLayerCollection是ImageryLayer的合集，提供添加、删除、显示、隐藏ImageryLayer的功能。
 */
class LICORE_EXPORT ImageryLayerCollection : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    ImageryLayerCollection(QObject *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~ImageryLayerCollection();

    /**
     * @brief
     * 返回当前ImageryLayer的数量
     * @return int
     */
    int length() const { return _layers.size(); }

    /**
     * @brief
     * 获取序号为i的ImageryLayer对象
     * @param i
     * @return ImageryLayer
     */
    ImageryLayer *get(int i) const;

    /**
     * @brief
     * 添加ImageryLayer对象
     * @param layer
     * ImageryLayer对象
     * @param index
     * 指定ImageryLayer对象的序号，如果为-1，则自动分配序号
     */
    void add(ImageryLayer *layer, int index = -1);

    /**
     * @brief
     * 添加ImageryProvider对象
     * @param provider
     * ImageryProvider对象
     * @param index
     * 指定ImageryProvider对象的序号，如果为-1，则自动分配序号
     */
    void addImageryProvider(ImageryProvider *provider, int index = -1);

    /**
     * @brief
     * 在合集中移除ImageryLayer
     * @param layer
     * ImageryLayer对象
     * @return bool 移除成功返回true，否则返回false
     */
    bool remove(ImageryLayer *layer);

    /**
     * @brief
     * 取消正在进行web墨卡托坐标转换的所有操作
     */
    void cancelReprojections();

    /**
     * @brief
     * 内部更新函数
     */
    void update();

signals:
    void layerAdded(ImageryLayer *layer, int index);
    void layerRemoved(ImageryLayer *layer);
    void layerMoved(ImageryLayer *layer);
    void layerShownOrHidden(ImageryLayer *layer);

private:
    QVector<ImageryLayer *> _layers; /**< TODO: describe */
};

#endif // IMAGERYLAYERCOLLECTION_H
