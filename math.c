#include "math.h"

float math_flt_degrees_to_radians(float degrees) {
    return degrees * MATH_FACTOR_DEG_TO_RAD;
}

float math_flt_radians_to_degrees(float radians) {
    return radians * MATH_FACTOR_RAD_TO_DEG;
}


float math_flt_interpolate_linear(float min, float max, float t) {
    return (max - min) * t + min;
}
