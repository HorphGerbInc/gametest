
#ifndef _SIMD_VEC4_HPP_
#define _SIMD_VEC4_HPP_

#include <Math/SIMD/SIMDVector.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      class Vec4 : public SIMDVector<Vec4, 4> {
      public:
        Vec4();
        Vec4(float x, float y, float z, float w);

        float X() const;
        float Y() const;
        float Z() const;
        float W() const;

        void SetX(float);
        void SetY(float);
        void SetZ(float);
        void SetW(float);
      };
    }
  }
}

#endif