#ifndef LITONEMAPPING_H
#define LITONEMAPPING_H

#include "licomponent.h"

class LiToneMappingPrivate;
class LiPostRendering;

/**
 * @brief
 * HDR渲染参数控制
 */
class LICORE_EXPORT LiToneMapping : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(float exposure READ exposure WRITE setExposure NOTIFY exposureChanged)
    Q_PROPERTY(float brightThreshold READ brightThreshold WRITE setBrightThreshold NOTIFY brightThresholdChanged)
    Q_PROPERTY(float bloomValue READ bloomValue WRITE setBloomValue NOTIFY bloomValueChanged)
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit LiToneMapping(QObject *parent = nullptr);

    /**
     * @brief
     * 是否进行HDR渲染，如果否，场景会进行普通渲染
     * @return bool
     */
    bool enabled() const;

    /**
     * @brief
     * 设置是否进行HDR渲染
     * @param enabled
     */
    void setEnabled(bool enabled);

    /**
     * @brief
     * 曝光强度
     * @return float 小于1表示偏暗，大于1表示偏亮
     */
    float exposure() const;

    /**
     * @brief
     * 设置曝光强度
     * @param exposure
     * 小于1表示偏暗，大于1表示偏亮
     */
    void setExposure(float exposure);

    /**
     * @brief
     * Bloom渲染时的亮度阈值
     * @return float 值越小Bloom效果越强，反之Bloom效果越弱
     */
    float brightThreshold() const;

    /**
     * @brief
     * 设置Bloom渲染时的亮度阈值
     * @param brightThreshold
     * 值越小Bloom效果越强，反之Bloom效果越弱
     */
    void setBrightThreshold(float brightThreshold);

    /**
     * @brief
     * 返回Bloom强度
     * @return float
     */
    float bloomValue() const;

    /**
     * @brief
     * 设置Bloom强度
     * @param bloomValue
     */
    void setBloomValue(float bloomValue);

signals:
    /**
     * @brief
     *
     */
    void enabledChanged();
    /**
     * @brief
     *
     */
    void brightThresholdChanged();
    /**
     * @brief
     *
     */
    void bloomValueChanged();
    /**
     * @brief
     *
     */
    void exposureChanged();

private:
    Q_DECLARE_PRIVATE(LiToneMapping)
    friend class LiPostRendering;
};

#endif // LITONEMAPPING_H
