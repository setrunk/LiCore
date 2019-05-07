#ifndef JULIANDATE_H
#define JULIANDATE_H

#include "licore_global.h"

namespace TimeConstants
{
    const double SECONDS_PER_MILLISECOND = 0.001; /**< TODO: describe */
    const double SECONDS_PER_MINUTE = 60.0; /**< TODO: describe */
    const double MINUTES_PER_HOUR = 60.0; /**< TODO: describe */
    const double HOURS_PER_DAY = 24.0; /**< TODO: describe */
    const double SECONDS_PER_HOUR = 3600.0; /**< TODO: describe */
    const double MINUTES_PER_DAY = 1440.0; /**< TODO: describe */
    const double SECONDS_PER_DAY = 86400.0; /**< TODO: describe */
    const double DAYS_PER_JULIAN_CENTURY = 36525.0; /**< TODO: describe */
    const double PICOSECOND = 0.000000001; /**< TODO: describe */
    const double MODIFIED_JULIAN_DATE_DIFFERENCE = 2400000.5; /**< TODO: describe */
}

namespace TimeStandard
{
    const int UTC = 0; /**< TODO: describe */
    const int TAI = 1; /**< TODO: describe */
}

/**
 * @brief
 * 儒略日，通常用于天文学的时间计算。
 */
class LICORE_EXPORT JulianDate
{
public:
    /**
     * @brief
     *
     */
    JulianDate();
    /**
     * @brief
     *
     * @param dayNumber
     * @param secondsOfDay
     * @param timeStandard
     */
    JulianDate(double dayNumber, double secondsOfDay, int timeStandard = TimeStandard::UTC);
    /**
     * @brief
     *
     * @param dateTime
     */
    JulianDate(const QDateTime &dateTime);

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator<(const JulianDate &other) const;

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const;
    /**
     * @brief
     *
     * @return int
     */
    int dayNumber() const { return m_dayNumber; }
    /**
     * @brief
     *
     * @return double
     */
    double totalDays() const { return m_dayNumber + (m_secondsOfDay/TimeConstants::SECONDS_PER_DAY); }
    /**
     * @brief
     *
     * @return double
     */
    double secondsOfDay() const { return m_secondsOfDay; }

    /**
     * @brief
     *
     * @param seconds
     */
    void addSeconds(double seconds);
    /**
     * @brief
     *
     * @param wholeDays
     * @param secondsOfDay
     */
    void setComponents(int wholeDays, double secondsOfDay);
    /**
     * @brief
     *
     */
    void convertUtcToTai();
    /**
     * @brief
     *
     */
    void convertTaiToUtc();
    /**
     * @brief
     *
     * @return double
     */
    double computeTaiMinusUtc() const;

    /**
     * @brief
     *
     * @return JulianDate
     */
    static JulianDate now();
    /**
     * @brief
     *
     * @param left
     * @param right
     * @return double
     */
    static double secondsDifference(const JulianDate &left, const JulianDate &right);
    /**
     * @brief
     *
     * @param left
     * @param right
     * @return double
     */
    static double daysDifference(const JulianDate &left, const JulianDate &right);
    /**
     * @brief
     *
     * @param left
     * @param right
     * @return int
     */
    static int compare(const JulianDate &left, const JulianDate &right);

private:
    int m_dayNumber; /**< TODO: describe */
    double m_secondsOfDay; /**< TODO: describe */
};

#endif // JULIANDATE_H
