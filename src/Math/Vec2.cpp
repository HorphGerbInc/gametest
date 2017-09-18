
#include <Math/Vec2.hpp>

namespace jerobins {
  namespace math {

    Vec2::Vec2() : VectorBase(2) { /*Empty */ }

    Vec2::Vec2(float x, float y) : VectorBase(2, x, y) {
      /* Empty */
    }

    float Vec2::X() const { return Get(0); }

    float Vec2::Y() const { return Get(1); }

  }
}
