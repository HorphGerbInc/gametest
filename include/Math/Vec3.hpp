
#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {

    class Vec3 : public ArrayVector<Vec3, 3> {
    public:
      Vec3();
      Vec3(float x, float y, float z);

      float X() const;
      float Y() const;
      float Z() const;

      void SetX(float);
      void SetY(float);
      void SetZ(float);

      // Cross Product
      Vec3 Cross(const Vec3 &&other) const;
    };
  }
}

#endif