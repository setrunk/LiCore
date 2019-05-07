#ifndef IMAGERY_H
#define IMAGERY_H

#include "licore_global.h"
#include "rectangle.h"
#include "cartesian4.h"
#include "lirequest.h"

class ImageryLayer;
class QuadtreeTile;
class FrameState;
class LiTexture;
class LiBuffer;
class LiGeometry;
class LiShaderProgram;

/**
 * @brief
 * 保存影像切片数据，一个影像切片数据，可能会被多个地球瓦片节点使用。
 */
class LICORE_EXPORT Imagery : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     */
    enum State
    {
        UNLOADED = 0,
        TRANSITIONING = 1,
        RECEIVED = 2,
        TEXTURE_LOADED = 3,
        READY = 4,
        FAILED = 5,
        INVALID = 6,
        PLACEHOLDER = 7,
        DESTROYED = 8
    };

    /**
     * @brief
     *
     * @param imageryLayer
     * @param x
     * @param y
     * @param level
     * @param rectangle
     */
    Imagery(ImageryLayer *imageryLayer, int x, int y, int level, const LiRectangle &rectangle = LiRectangle());
    /**
     * @brief
     *
     */
    ~Imagery();

    /**
     * @brief
     *
     * @return ImageryLayer
     */
    ImageryLayer *imageryLayer() const { return _imageryLayer; }
    /**
     * @brief
     *
     * @return Imagery
     */
    Imagery *parentImagery() { return _parent; }
    /**
     * @brief
     *
     * @return const LiRectangle
     */
    const LiRectangle &rectangle() const { return _rectangle; }

    /**
     * @brief
     *
     * @return int
     */
    int x() const { return _x; }
    /**
     * @brief
     *
     * @return int
     */
    int y() const { return _y; }
    /**
     * @brief
     *
     * @return int
     */
    int level() const { return _level; }

    /**
     * @brief
     *
     * @return State
     */
    State state() const { return _state; }
    /**
     * @brief
     *
     * @param state
     */
    void setState(const State &state) { _state = state; }

    /**
     * @brief
     *
     * @return QUrl
     */
    QUrl url() const { return _imageUrl; }
    /**
     * @brief
     *
     * @param url
     */
    void setUrl(const QUrl &url) { _imageUrl = url; }

    /**
     * @brief
     *
     * @return bool
     */
    bool isDestroyed() const { return DESTROYED == _state; }

    /**
     * @brief
     *
     * @return bool
     */
    bool show() const;

    /**
     * @brief
     *
     * @return QImage
     */
    QImage image() const { return _image; }
    /**
     * @brief
     *
     * @param image
     */
    void setImage(const QImage &image);

    /**
     * @brief
     *
     * @return LiTexture
     */
    LiTexture *texture() const { return _texture; }
    /**
     * @brief
     *
     * @return LiTexture
     */
    LiTexture *textureWebMercator() const { return _textureWebMercator; }
    /**
     * @brief
     *
     * @return Vector4
     */
    Vector4 mercatorParameters() const { return _mecatorParameters; }

    /**
     * @brief
     *
     */
    void addReference();
    /**
     * @brief
     *
     * @return int
     */
    int releaseReference();

    /**
     * @brief
     *
     */
    void freeResources();
    /**
     * @brief
     *
     */
    void createTexture(bool needGeographicProjection);

    /**
     * @brief
     *
     * @param frameState
     * @param needGeographicProjection
     * @param priorityFunc
     */
    void processStateMachine(FrameState *frameState, bool needGeographicProjection, PriorityFunction priorityFunc);

    /**
     * @brief
     *
     * @param imageryLayer
     * @return Imagery
     */
    static Imagery *createPlaceholder(ImageryLayer *imageryLayer);

private:
    /**
     * @brief
     *
     */
    void computeMercatorParameters();
    /**
     * @brief
     *
     * @param frameState
     * @param needGeographicProjection
     */
    void reprojectTexture(FrameState *frameState, bool needGeographicProjection = true);
    /**
     * @brief
     *
     * @param fs
     * @param texture
     */
    void reprojectToGeographic(FrameState *fs, LiTexture *texture);
    /**
     * @brief
     *
     */
    void finalizeReprojectTexture();

    /**
     * @brief
     *
     */
    struct CacheData {
        LiBuffer *positionBuffer = nullptr; /**< TODO: describe */
        LiShaderProgram *shaderProgram = nullptr; /**< TODO: describe */
    };
    static CacheData m_cacheData; /**< TODO: describe */

    ImageryLayer *_imageryLayer; /**< TODO: describe */
    int _x; /**< TODO: describe */
    int _y; /**< TODO: describe */
    int _level; /**< TODO: describe */
    Imagery *_parent; /**< TODO: describe */
    State _state; /**< TODO: describe */
    QUrl _imageUrl; /**< TODO: describe */
    QImage _image; /**< TODO: describe */
    LiTexture *_texture; /**< TODO: describe */
    LiTexture *_textureWebMercator; /**< TODO: describe */
    LiGeometry *_webMercatorTGeometry;
    LiRectangle _rectangle; /**< TODO: describe */
    Vector4 _mecatorParameters; /**< TODO: describe */
    int _referenceCount; /**< TODO: describe */
};

#endif // IMAGERY_H
