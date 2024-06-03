#ifndef _UTILS_COLLECTION_MATH_H
#define _UTILS_COLLECTION_MATH_H

#include <math.h>

#define MATH_FACTOR_DEG_TO_RAD (M_PI / 180.0)
#define MATH_FACTOR_RAD_TO_DEG (180.0 / M_PI)

/*
 * Convert degrees to radians (32-bit float variant).
 */
float math_flt_degrees_to_radians(float degrees);

/*
 * Convert radians to degrees (32-bit float variant).
 */
float math_flt_radians_to_degrees(float radians);

/*
 * Linearly interpolate between the min and max values, based on t.
 * t must be in the interval [0, 1].
 */
float math_flt_interpolate_linear(float min, float max, float t);

#endif /* _UTILS_COLLECTION_MATH_H */
