#ifndef LITIMESYSTEM_H
#define LITIMESYSTEM_H

#include "liabstractsystem.h"

class LiTimeSystemPrivate;

/**
 * @brief
 * 时间系统，在创建时开始运行，提供获取系统运行时间功能。
 */
class LICORE_EXPORT LiTimeSystem : public LiAbstractSystem
{
    Q_OBJECT
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiTimeSystem(QObject *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiTimeSystem();

    /**
     * @brief
     * 开始计时
     */
    void start();

    /**
     * @brief
     * 重新开始计时
     */
    void restart();

    /**
     * @brief
     * 获取从系统开始运行的时间
     * @return quint64 毫秒（microsecond）
     */
    quint64 time() const;

    /**
     * @brief
     * 获取从系统开始运行的时间
     * @return double 秒（second）
     */
    Q_INVOKABLE double timeSeconds() const;

    /**
     * @brief
     * 获取上一帧的间隔时间
     * @return quint64 毫秒（microsecond）
     */
    quint64 delta() const;

    /**
     * @brief
     * 获取上一帧的间隔时间
     * @return double 秒（second）
     */
    Q_INVOKABLE double deltaSeconds() const;

    /**
     * @brief
     * 获取操作系统的时间戳
     * @return quint64 毫秒（microsecond）
     */
    quint64 timeStamp() const;

    /**
     * @brief
     * 获取操作系统的时间戳
     * @return double 秒（second）
     */
    Q_INVOKABLE double timeStampSeconds() const;

    /**
     * @brief
     * 获取setDateTime函数设置的日期时间，默认为空的QDateTime
     * @return QDateTime
     */
    QDateTime dateTime() const;

    /**
     * @brief
     * 设置当前的日期时间，太阳的位置会根据设置的日期时间重新计算
     * @param dateTime 自定义日期时间
     */
    Q_INVOKABLE void setDateTime(const QDateTime &dateTime);
    Q_INVOKABLE void setYear(int year);
    Q_INVOKABLE void setMonth(int month);
    Q_INVOKABLE void setDay(int day);
    Q_INVOKABLE void setHour(int hour);
    Q_INVOKABLE void setMinute(int minute);
    Q_INVOKABLE void setSecond(int second);

private:
    void onEngineStartup() override;
    void onEngineShutdown() override;
    void beginFrame() override;
    void update() override;
    void endFrame() override;

    Q_DECLARE_PRIVATE(LiTimeSystem)
    friend class LiEngine;
};

#endif // LITIMESYSTEM_H
