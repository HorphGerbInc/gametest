
#include <Math/SIMD/Vec3.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      Vec3::Vec3() : SIMDVector() { /*Empty */
      }

      Vec3::Vec3(float x, float y, float z) : SIMDVector(x, y, z) {
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
        __m128 us = this->RawSIMD();
        __m128 them = other.RawSIMD();

        __m128 a =
            _mm_mul_ps(them, _mm_shuffle_ps(us, us, _MM_SHUFFLE(3, 0, 2, 1)));
        __m128 b =
            _mm_mul_ps(us, _mm_shuffle_ps(them, them, _MM_SHUFFLE(3, 0, 2, 1)));
        __m128 tmp = _mm_sub_ps(a, b);
        tmp = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(3, 0, 2, 1));
        float array[4];
        _mm_store_ps(array, tmp);
        Vec3 result;
        for (int i = 0; i < 3; ++i) {
          result.Set(i, array[i]);
        }
        return result;
      }
    }
  }
}