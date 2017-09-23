
#include <Math/SIMD/Vec2.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      Vec2::Vec2() { /*Empty */
      }

      Vec2::Vec2(float x, float y) : SIMDVector(x, y) { /* Empty */
      }

      float Vec2::X() const { return Get(0); }

      float Vec2::Y() const { return Get(1); }

      void Vec2::SetX(float newX) { Set(0, newX); }

      void Vec2::SetY(float newY) { Set(1, newY); }
    }
  }
}