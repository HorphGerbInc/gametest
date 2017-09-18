
#include <Math/Vec3.hpp>

namespace jerobins {
  namespace math {

    Vec3::Vec3() : VectorBase(3) { /*Empty */
    }

    Vec3::Vec3(float x, float y, float z) : VectorBase(3, x, y, z) {
      /* Empty */
    }

    float Vec3::X() const { return Get(0); }

    float Vec3::Y() const { return Get(1); }

    float Vec3::Z() const { return Get(2); }

    void Vec3::SetX(float newX) { return Set(0, newX); }

    void Vec3::SetY(float newY) { return Set(1, newY); }

    void Vec3::SetZ(float newZ) { return Set(2, newZ); }

    // Cross Product
    Vec3 Vec3::Cross(const Vec3 &&other) const {
      __m128 a =
          _mm_mul_ps(other.xmm_, _mm_shuffle_ps(this->xmm_, this->xmm_,
                                                _MM_SHUFFLE(3, 0, 2, 1)));
      __m128 b =
          _mm_mul_ps(this->xmm_, _mm_shuffle_ps(other.xmm_, other.xmm_,
                                                _MM_SHUFFLE(3, 0, 2, 1)));
      __m128 tmp = _mm_sub_ps(a, b);
      tmp = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(3, 0, 2, 1));

      Vec3 result;
      result.xmm_ = tmp;
      return result;
    }
  }
}
