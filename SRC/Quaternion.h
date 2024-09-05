#include "Vector.hpp"

#define toRadians(x) x * 0.01745329251f

class Quaternion
{
public:
    Quaternion()
    {
        w =0 ; v = Vector3(0, 0, 0);
    }
    Quaternion(const float &W, const Vector3& V)
    {
        w = W;
        v = V;
    }
    Quaternion(const Vector3& axis, const float &angle)
    {
        // convert angle to radians
        float a = toRadians(angle);
        float s = std::sin(a / 2);
        w = std::cos(a / 2);
        v = axis * s;
    }

    const Quaternion Inverted() const
    {
        return Quaternion(w, Vector3(-v.x, -v.y, -v.z));
    }

    const Quaternion operator*(const Quaternion &q) const
    {
        Quaternion r;

	    r.w = w*q.w - v.DotProduct(q.v);
	    r.v = v*q.w + q.v*w + v.Cross(q.v);

	    return r;
    }
    const Quaternion operator=(const Quaternion &q)
    {
        w = q.w;
        v = q.v;
        return *this;
    }
    const Vector3 operator*(const Vector3 &v) const
    {
        const Quaternion p(0, v);
        const Quaternion q = *this;
        return (q * p * q.Inverted()).v;   
    }
    float w;
    Vector3 v;
};