
#include <Math/Vec3.hpp>

namespace jerobins {
  namespace math {

    Vec3::Vec3()  { /*Empty */
    }

    Vec3::Vec3(float x, float y, float z) : ArrayVector(x, y, z) { /* Empty */
    }

    float Vec3::X() const { return Get(0); }

    float Vec3::Y() const { return Get(1); }

    float Vec3::Z() const { return Get(2); }

    void Vec3::SetX(float newX) { return Set(0, newX); }

    void Vec3::SetY(float newY) { return Set(1, newY); }

    void Vec3::SetZ(float newZ) { return Set(2, newZ); }

    // Cross Product
    Vec3 Vec3::Cross(const Vec3 &&other) const {
      float x = Y() * other.Z() - other.Z() * Y();
      float y = Z() * other.X() - other.X() * Z();
      float z = X() * other.Y() - other.Y() * X();
      Vec3 result(x, y, z);
      return result;
    }
  }
}
