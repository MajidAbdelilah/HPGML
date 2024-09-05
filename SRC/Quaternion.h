#include "Vector.hpp"

#define toRadians(x) x * 0.01745329251f

class Quaternion
{
public:
    Quaternion()
    {
        w = x = y = z = 0;
    }
    Quaternion(const float &W, const float &X, const float &Y, const float &Z)
    {
        w = W;
        x = X;
        y = Y;
        z = Z;
    }
    Quaternion(const Vector3& axis, const float &angle)
    {
        // convert angle to radians
        float a = toRadians(angle);
        float s = std::sin(a / 2);
        w = std::cos(a / 2);
        x = axis.x * s;
        y = axis.y * s;
        z = axis.z * s;
    }

    const Quaternion Inverted() const
    {
        return Quaternion(w, -x, -y, -z);
    }

    float w, x, y, z;
};