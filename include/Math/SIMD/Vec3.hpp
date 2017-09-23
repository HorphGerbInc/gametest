
#ifndef _SIMD_VEC3_HPP_
#define _SIMD_VEC3_HPP_

#include <Math/SIMD/SIMDVector.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      class Vec3 : public SIMDVector<Vec3, 3> {
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
}

#endif