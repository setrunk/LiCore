#ifndef LIRENDERSYSTEM_H
#define LIRENDERSYSTEM_H

#include "liabstractsystem.h"

class LiCamera;
class LiScene;
class LiTexture;
class LiAmbientOcclusion;
class LiPostRendering;
class LiToneMapping;
class LiRenderViewport;
class LiWaterParameters;
class LiRenderSystemPrivate;
class SMAA;

/**
 * @brief
 * LiRenderSystem是LiEngine的一个子系统，属于ECS架构中的System的一部分，负责所有渲染相关任务的调度和运行。
 */
class LICORE_EXPORT LiRenderSystem : public LiAbstractSystem
{
    Q_OBJECT
    Q_PROPERTY(LiAmbientOcclusion* ssao READ ssao)
    Q_PROPERTY(LiToneMapping* toneMapping READ toneMapping)
    Q_PROPERTY(LiPostRendering* postRendering READ postRendering)
    Q_PROPERTY(LiWaterParameters* waterParameters READ waterParameters)
    Q_PROPERTY(SMAA* smaa READ smaa)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiRenderSystem(QObject *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiRenderSystem();

    /**
     * @brief
     * 是否采用延时渲染方式
     * @return bool
     */
    bool isDeferredRendering() const;

    /**
     * @brief
     * 对海量点光源的渲染，会根据该参数进行网格切分，
     * 网格内所有的点光源，会作为一个整体进行计算，
     * 可以极大提高效率。
     * @return float 默认值为200.0
     */
    float pointLightGridSize() const;

    /**
     * @brief
     * 设置点光源网格划分的网格大小，默认为200.0
     * @param size
     */
    void setPointLightGridSize(float size);

    /**
     * @brief
     * 返回渲染缓存中的颜色缓存对象，是延时渲染中MRT的Diffuse纹理
     * @return LiTexture
     */
    LiTexture *colorTexture() const;

    /**
     * @brief
     * 返回渲染缓存中的线性（0-1）深度缓存对象，是延时渲染中MRT的Depth纹理
     * @return LiTexture
     */
    LiTexture *depthTexture() const;

    /**
     * @brief
     * 返回渲染缓存中的法线缓存对象，是延时渲染中MRT的Normal纹理
     * @return LiTexture
     */
    LiTexture *normalTexture() const;

    /**
     * @brief
     * 返回屏幕空间环境光遮挡SSAO的参数控制对象
     * @return LiAmbientOcclusion
     */
    LiAmbientOcclusion *ssao() const;

    /**
     * 返回全屏抗锯齿SMAA对象
     */
    SMAA *smaa() const;

    /**
     * @brief
     * 返回HDR渲染的色调映射参数控制对象
     * @return LiToneMapping
     */
    LiToneMapping *toneMapping() const;

    /**
     * @brief
     * 返回HDR渲染的后期调色参数控制对象
     * @return LiPostRendering
     */
    LiPostRendering *postRendering() const;

    /**
     * @brief
     * 返回水面渲染的参数控制对象
     * @return LiWaterParameters
     */
    LiWaterParameters *waterParameters() const;

    /**
     * @brief
     * 添加渲染视窗
     * @param viewport
     */
    void addRenderViewport(LiRenderViewport *viewport);

    /**
     * @brief
     * 移除渲染视窗
     * @param viewport
     */
    void removeRenderViewport(LiRenderViewport *viewport);

    /**
     * @brief
     * 返回所有的渲染视窗合集
     * @return QVector<LiRenderViewport *>
     */
    QVector<LiRenderViewport *> renderViewports() const;

private:
    void onEngineShutdown();
    void beginFrame();
    void update();
    void endFrame();
    void render(LiCamera *camera);
    void draw(LiEntity *entity);
    Q_DECLARE_PRIVATE(LiRenderSystem)
    friend class LiScene;
};

#endif // LIRENDERSYSTEM_H
