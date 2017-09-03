
#include <Math/Vec3.hpp>

namespace jerobins
{
namespace math
{

Vec3::Vec3() { /*Empty */ }

Vec3::Vec3(float x, float y, float z)
{
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
}

Vec3::Vec3(const float *data)
{
    data_[0] = data[0];
    data_[1] = data[1];
    data_[2] = data[2];
}

Vec3::Vec3(const Vec3 &&other)
{
    this->xmm_ = other.xmm_;
}

Vec3::Vec3(const Vec3 &other)
{
    this->xmm_ = other.xmm_;
}

// Cross Product
Vec3 Vec3::Cross(const Vec3 &&other) const
{
    __m128 a = _mm_mul_ps(other.xmm_, _mm_shuffle_ps(this->xmm_, this->xmm_, _MM_SHUFFLE(3, 0, 2, 1)));
    __m128 b = _mm_mul_ps(this->xmm_, _mm_shuffle_ps(other.xmm_, other.xmm_, _MM_SHUFFLE(3, 0, 2, 1)));
    __m128 tmp = _mm_sub_ps(a, b);
    tmp = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(3, 0, 2, 1));

    Vec3 result;
    result.xmm_ = tmp;
    return result;
}
}
}
