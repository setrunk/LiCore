#ifndef EXPOSURE_H
#define EXPOSURE_H

#include "licore_global.h"

/**
 * A series of utilities to compute exposure, exposure value at ISO 100 (EV100),
 * luminance and illuminance using a physically-based camera model.
 */
namespace Exposure {

/**
 * Returns the exposure value (EV at ISO 100) of the specified exposure parameters.
 */
LICORE_EXPORT float ev100(float aperture, float shutterSpeed, float sensitivity) noexcept;

/**
 * Returns the exposure value (EV at ISO 100) for the given average luminance (in @f$ \frac{cd}{m^2} @f$).
 */
LICORE_EXPORT float ev100FromLuminance(float luminance) noexcept;

/**
* Returns the exposure value (EV at ISO 100) for the given illuminance (in lux).
*/
LICORE_EXPORT float ev100FromIlluminance(float illuminance) noexcept;

/**
 * Returns the photometric exposure for the specified exposure parameters.
 * This function is equivalent to calling `exposure(ev100(aperture, shutterSpeed, sensitivity))`
 * but is slightly faster and offers higher precision.
 */
LICORE_EXPORT float exposure(float aperture, float shutterSpeed, float sensitivity) noexcept;

/**
 * Returns the photometric exposure for the given EV100.
 */
LICORE_EXPORT float exposure(float ev100) noexcept;

/**
 * Returns the incident luminance in @f$ \frac{cd}{m^2} @f$ for the specified exposure parameters of
 * a camera acting as a spot meter.
 * This function is equivalent to calling `luminance(ev100(aperture, shutterSpeed, sensitivity))`
 * but is slightly faster and offers higher precision.
 */
LICORE_EXPORT float luminance(float aperture, float shutterSpeed, float sensitivity) noexcept;

/**
 * Converts the specified EV100 to luminance in @f$ \frac{cd}{m^2} @f$.
 * EV100 is not a measure of luminance, but an EV100 can be used to denote a
 * luminance for which a camera would use said EV100 to obtain the nominally
 * correct exposure
 */
LICORE_EXPORT float luminance(float ev100) noexcept;

/**
 * Returns the illuminance in lux for the specified exposure parameters of
 * a camera acting as an incident light meter.
 * This function is equivalent to calling `illuminance(ev100(aperture, shutterSpeed, sensitivity))`
 * but is slightly faster and offers higher precision.
 */
LICORE_EXPORT float illuminance(float aperture, float shutterSpeed, float sensitivity) noexcept;

/**
 * Converts the specified EV100 to illuminance in lux.
 * EV100 is not a measure of illuminance, but an EV100 can be used to denote an
 * illuminance for which a camera would use said EV100 to obtain the nominally
 * correct exposure.
 */

LICORE_EXPORT float illuminance(float ev100) noexcept;

}

#endif // EXPOSURE_H
