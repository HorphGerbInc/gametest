
#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <Math/VectorBase.hpp>

namespace jerobins {
  namespace math {

    class Vec3 : public VectorBase<Vec3> {
    public:
      Vec3();
      Vec3(float x, float y, float z);
      Vec3(const float *data);
      Vec3(const Vec3 &&other);
      Vec3(const Vec3 &other);

      // Cross Product
      Vec3 Cross(const Vec3 &&other) const;
    };
  }
}

#endif