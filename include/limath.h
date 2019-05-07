#ifndef LIMATH_H
#define LIMATH_H

#include <math.h>
#include <vector>
#include <float.h>

#undef min
#undef max

namespace Math
{
    static const double EPSILON1 = 0.1;
    static const double EPSILON2 = 0.01;
    static const double EPSILON3 = 0.001;
    static const double EPSILON4 = 0.0001;
    static const double EPSILON5 = 0.00001;
    static const double EPSILON6 = 0.000001;
    static const double EPSILON7 = 0.0000001;
    static const double EPSILON8 = 0.00000001;
    static const double EPSILON9 = 0.000000001;
    static const double EPSILON10 = 0.0000000001;
    static const double EPSILON11 = 0.00000000001;
    static const double EPSILON12 = 0.000000000001;
    static const double EPSILON13 = 0.0000000000001;
    static const double EPSILON14 = 0.00000000000001;
    static const double EPSILON15 = 0.000000000000001;
    static const double EPSILON16 = 0.0000000000000001;
    static const double EPSILON17 = 0.00000000000000001;
    static const double EPSILON18 = 0.000000000000000001;
    static const double EPSILON19 = 0.0000000000000000001;
    static const double EPSILON20 = 0.00000000000000000001;

    static const double GRAVITATIONALPARAMETER = 3.986004418e14;

    static const double SOLAR_RADIUS = 6.955e8;
    static const double LUNAR_RADIUS = 1737400.0;

    static const double SIXTY_FOUR_KILOBYTES = 64 * 1024;

    static const double PI = 3.1415926535897932384626433832795;
    static const double ONE_OVER_PI = 1.0 / PI;
    static const double PI_OVER_TWO = PI / 2.0;
    static const double PI_OVER_THREE = PI / 3.0;
    static const double PI_OVER_FOUR = PI / 4.0;
    static const double PI_OVER_SIX = PI / 6.0;
    static const double THREE_PI_OVER_TWO = (3.0 * PI) * 0.5;
    static const double TWO_PI = 2.0 * PI;
    static const double ONE_OVER_TWO_PI = 1.0 / (2.0 * PI);

    static const double RADIANS_PER_DEGREE = PI / 180.0;
    static const double DEGREES_PER_RADIAN = 180.0 / PI;
    static const double RADIANS_PER_ARCSECOND = RADIANS_PER_DEGREE / 3600.0;

    inline double toRadians(double degrees) {
        return degrees * RADIANS_PER_DEGREE;
    }

    inline double toDegrees(double radians) {
        return radians * DEGREES_PER_RADIAN;
    }

    inline double sign(double value) {
        return value > 0 ? 1 : (value < 0 ? -1 : 0);
    }

    inline double signNotZero(double value) {
        return value < 0.0 ? -1.0 : 1.0;
    }

    inline double clamp(double value, double minValue, double maxValue)
    {
        return value < minValue ? minValue : (value > maxValue ? maxValue : value);
    }

    /**
         * Converts a scalar value in the range [-1.0, 1.0] to a SNORM in the range [0, rangeMax]
         * @param {Number} value The scalar value in the range [-1.0, 1.0]
         * @param {Number} [rangeMax=255] The maximum value in the mapped range, 255 by default.
         * @returns {Number} A SNORM value, where 0 maps to -1.0 and rangeMax maps to 1.0.
         *
         * @see Math.fromSNorm
         */
    inline double toSNorm(double value, int rangeMax = 255) {
        //            rangeMax = defaultValue(rangeMax, 255);
        return round((Math::clamp(value, -1.0, 1.0) * 0.5 + 0.5) * rangeMax);
    }

    /**
         * Converts a SNORM value in the range [0, rangeMax] to a scalar in the range [-1.0, 1.0].
         * @param {Number} value SNORM value in the range [0, 255]
         * @param {Number} [rangeMax=255] The maximum value in the SNORM range, 255 by default.
         * @returns {Number} Scalar in the range [-1.0, 1.0].
         *
         * @see Math.toSNorm
         */
    inline double fromSNorm(double value, int rangeMax = 255) {
        //            rangeMax = defaultValue(rangeMax, 255);
        return Math::clamp(value, 0.0, rangeMax) / rangeMax * 2.0 - 1.0;
    }

    inline double sinh(int value) {
        double part1 = pow(2.718281828459045, value);
        double part2 = pow(2.718281828459045, -value);
        return (part1 - part2) * 0.5;
    }

    inline double cosh(int value) {
        double part1 = pow(2.718281828459045, value);
        double part2 = pow(2.718281828459045, -value);
        return (part1 + part2) * 0.5;
    }

    /**
         * Computes the linear interpolation of two values.
         *
         * @param {Number} p The start value to interpolate.
         * @param {Number} q The end value to interpolate.
         * @param {Number} time The time of interpolation generally in the range <code>[0.0, 1.0]</code>.
         * @returns {Number} The linearly interpolated value.
         */
    template <typename T>
    inline T lerp(const T &p, const T &q, double time) {
        return p * (1.0 - time) + q * time;
    }

    /**
         * Converts a longitude value, in radians, to the range [<code>-Math.PI</code>, <code>Math.PI</code>).
         *
         * @param {Number} angle The longitude value, in radians, to convert to the range [<code>-Math.PI</code>, <code>Math.PI</code>).
         * @returns {Number} The equivalent longitude value in the range [<code>-Math.PI</code>, <code>Math.PI</code>).
         */
    inline double convertLongitudeRange(double angle) {
        double twoPi = TWO_PI;
        double simplified = angle - floor(angle / twoPi) * twoPi;
        if (simplified < -PI) {
            return simplified + twoPi;
        }
        if (simplified >= PI) {
            return simplified - twoPi;
        }
        return simplified;
    }

    /**
         * Convenience function that clamps a latitude value, in radians, to the range [<code>-Math.PI/2</code>, <code>Math.PI/2</code>).
         * Useful for sanitizing data before use in objects requiring correct range.
         *
         * @param {Number} angle The latitude value, in radians, to clamp to the range [<code>-Math.PI/2</code>, <code>Math.PI/2</code>).
         * @returns {Number} The latitude value clamped to the range [<code>-Math.PI/2</code>, <code>Math.PI/2</code>).
         */
    inline double clampToLatitudeRange(double angle) {
        return clamp(angle, -1*PI_OVER_TWO, PI_OVER_TWO);
    }

    /**
         * The modulo operation that also works for negative dividends.
         *
         * @param {Number} m The dividend.
         * @param {Number} n The divisor.
         * @returns {Number} The remainder.
         */
    inline double mod(double m, double n) {
        return fmod(fmod(m, n) + n, n);
    }

    /**
         * Produces an angle in the range 0 <= angle <= 2Pi which is equivalent to the provided angle.
         *
         * @param {Number} angle in radians
         * @returns {Number} The angle in the range [0, <code>Math.TWO_PI</code>].
         */
    inline double zeroToTwoPi(double angle) {
        double f = mod(angle, TWO_PI);
        if (abs(f) < EPSILON14 && abs(angle) > EPSILON14) {
            return TWO_PI;
        }
        return f;
    }

    /**
         * Produces an angle in the range -Pi <= angle <= Pi which is equivalent to the provided angle.
         *
         * @param {Number} angle in radians
         * @returns {Number} The angle in the range [<code>-Math.PI</code>, <code>Math.PI</code>].
         */
    inline double negativePiToPi(double angle) {
        return zeroToTwoPi(angle + PI) - PI;
    }

    inline double min(double a, double b) {
        return a < b ? a : b;
    }

    inline double min(double a, double b, double c) {
        return a < b ? min(a, c) : min(b, c);
    }

    inline double min(double a, double b, double c, double d) {
        return a < b ? min(a, c, d) : min(b, c, d);
    }

    inline double max(double a, double b) {
        return a > b ? a : b;
    }

    inline double max(double a, double b, double c) {
        return a > b ? max(a, c) : max(b, c);
    }

    inline double max(double a, double b, double c, double d) {
        return a > b ? max(a, c, d) : max(b, c, d);
    }

    inline double step(double value, double left, double right)
    {
        return (value - left) / (right - left);
    }

    /**
         * Determines if two values are equal using an absolute or relative tolerance test. This is useful
         * to avoid problems due to roundoff error when comparing floating-point values directly. The values are
         * first compared using an absolute tolerance test. If that fails, a relative tolerance test is performed.
         * Use this test if you are unsure of the magnitudes of left and right.
         *
         * @param {Number} left The first value to compare.
         * @param {Number} right The other value to compare.
         * @param {Number} relativeEpsilon The maximum inclusive delta between <code>left</code> and <code>right</code> for the relative tolerance test.
         * @param {Number} [absoluteEpsilon=relativeEpsilon] The maximum inclusive delta between <code>left</code> and <code>right</code> for the absolute tolerance test.
         * @returns {Boolean} <code>true</code> if the values are equal within the epsilon; otherwise, <code>false</code>.
         */
    inline bool equalsEpsilon(double left, double right, double epsilon) {
        double absDiff = abs(left - right);
        return absDiff <= epsilon || absDiff <= epsilon * max(abs(left), abs(right));
    }

    //        var factorials = [1];

    /**
         * Computes the factorial of the provided number.
         *
         * @param {Number} n The number whose factorial is to be computed.
         * @returns {Number} The factorial of the provided number or undefined if the number is less than 0.
         *
         * @exception {DeveloperError} A number greater than or equal to 0 is required.
         *
         * @see {@link http://en.wikipedia.org/wiki/Factorial|Factorial on Wikipedia}
         */
    inline int factorial(int n) {
        static bool first = 1;
        static std::vector<int> factorials;
        if (first)
        {
            factorials.push_back(1);
            first = false;
        }

        int length = factorials.size();
        if (n >= length) {
            int sum = factorials[length - 1];
            for (int i = length; i <= n; i++) {
                factorials.push_back(sum * i);
            }
        }
        return factorials[n];
    }

    /**
         * Increments a number with a wrapping to a minimum value if the number exceeds the maximum value.
         *
         * @param {Number} [n] The number to be incremented.
         * @param {Number} [maximumValue] The maximum incremented value before rolling over to the minimum value.
         * @param {Number} [minimumValue=0.0] The number reset to after the maximum value has been exceeded.
         * @returns {Number} The incremented number.
         *
         * @exception {DeveloperError} Maximum value must be greater than minimum value.
         */
    inline int incrementWrap(int n, int maximumValue, int minimumValue = 0) {
        //            minimumValue = defaultValue(minimumValue, 0.0);
        ++n;
        if (n > maximumValue) {
            n = minimumValue;
        }
        return n;
    }

    inline bool isPowerOfTwo(int n) {
        return (n != 0) && ((n & (n - 1)) == 0);
    }

    inline int nextPowerOfTwo(int n) {
        // From http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
        --n;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        ++n;

        return n;
    }

    //        var randomNumberGenerator = new MersenneTwister();

    /**
         * Sets the seed used by the random number generator
         * in {@link Math#nextRandomNumber}.
         *
         * @param {Number} seed An integer used as the seed.
         */
    //        Math.setRandomNumberSeed = function(seed) {
    //            //>>includeStart('debug', pragmas.debug);
    //            if (!defined(seed)) {
    //                throw new DeveloperError('seed is required.');
    //            }
    //            //>>includeEnd('debug');

    //            randomNumberGenerator = new MersenneTwister(seed);
    //        };

    /**
         * Generates a random number in the range of [0.0, 1.0)
         * using a Mersenne twister.
         *
         * @returns {Number} A random number in the range of [0.0, 1.0).
         *
         * @see Math.setRandomNumberSeed
         * @see {@link http://en.wikipedia.org/wiki/Mersenne_twister|Mersenne twister on Wikipedia}
         */
    //        static double nextRandomNumber() {
    //            return randomNumberGenerator.random();
    //        }

    /**
         * Computes <code>Math.acos(value)</acode>, but first clamps <code>value</code> to the range [-1.0, 1.0]
         * so that the function will never return NaN.
         *
         * @param {Number} value The value for which to compute acos.
         * @returns {Number} The acos of the value if the value is in the range [-1.0, 1.0], or the acos of -1.0 or 1.0,
         *          whichever is closer, if the value is outside the range.
         */
    inline double acosClamped(double value) {
        return acos(Math::clamp(value, -1.0, 1.0));
    }

    /**
         * Computes <code>Math.asin(value)</acode>, but first clamps <code>value</code> to the range [-1.0, 1.0]
         * so that the function will never return NaN.
         *
         * @param {Number} value The value for which to compute asin.
         * @returns {Number} The asin of the value if the value is in the range [-1.0, 1.0], or the asin of -1.0 or 1.0,
         *          whichever is closer, if the value is outside the range.
         */
    inline double asinClamped(double value) {
        return asin(Math::clamp(value, -1.0, 1.0));
    }

    /**
         * Finds the chord length between two points given the circle's radius and the angle between the points.
         *
         * @param {Number} angle The angle between the two points.
         * @param {Number} radius The radius of the circle.
         * @returns {Number} The chord length.
         */
    inline double chordLength(double angle, double radius) {
        return 2.0 * radius * sin(angle * 0.5);
    }

    inline double logBase(double number, double base) {
        return log(number) / log(base);
    }

    inline double fog(double distanceToCamera, double density) {
        double scalar = distanceToCamera * density;
        return 1.0 - exp(-(scalar * scalar));
    }

    inline unsigned short tofloat16(float f)
    {
        unsigned int *i = (unsigned int *)&f;
        unsigned int sign = (*i >> 31) & 0x1;
        unsigned int exponent = ((*i >> 23) & 0xff) - 0x7f;
        unsigned int mantissa = (*i) & 0x7fffff;

        exponent += 0x7;
        unsigned short ret = ((sign & 0x1) << 15);
        ret |= (exponent & 0xf) << 11;
        ret |= (mantissa  >> 13) & 0x7ff;
        return ret;
    }

    inline unsigned int tofloat32(unsigned short f)
    {
        unsigned short *i = (unsigned short *)&f;
        unsigned int sign = (*i >> 15) & 0x1;
        unsigned int exponent = ((*i >> 11) & 0xf) - 0x7;
        unsigned int mantissa = (*i) & 0x7ff;

        exponent += 0x7f;
        unsigned int ret = ((sign & 0x1) << 31);
        ret |= (exponent & 0xff) << 23;
        ret |= (mantissa << 13) & 0x7fffff;
        return ret;
    }

    inline double frand()
    {
        static double t = 1.0 / RAND_MAX;
        return t * ::rand();
    }

}

#endif // LIMATH_H
