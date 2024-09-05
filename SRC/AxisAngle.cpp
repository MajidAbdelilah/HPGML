#include "AxisAngle.h"


//axis need to be a normalized vector
Vector3 RotateVectorAroundAxisAngle(const Vector3& v, const Vector3& axis, float angle)
{
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);

    return v * cosAngle + axis.Cross(v) * sinAngle + axis * axis.DotProduct(v) * (1 - cosAngle);
}