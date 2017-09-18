
#include <Math/Vec4.hpp>

namespace jerobins {
  namespace math {

    Vec4::Vec4() : VectorBase(4) { /* Empty */
    }

    Vec4::Vec4(float x, float y, float z, float w) : VectorBase(4, x, y, z, w) {
      /* Empty */
    }

    float Vec4::X() const { return Get(0); }
    float Vec4::Y() const { return Get(1); }
    float Vec4::Z() const { return Get(2); }
    float Vec4::W() const { return Get(3); }

    void Vec4::SetX(float newX) { return Set(0, newX); }
    void Vec4::SetY(float newY) { return Set(1, newY); }
    void Vec4::SetZ(float newZ) { return Set(2, newZ); }
    void Vec4::SetW(float newW) { return Set(3, newW); }
  }
}
