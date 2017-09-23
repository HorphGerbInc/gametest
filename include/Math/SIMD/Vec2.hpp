
#ifndef _SIMD_VEC2_HPP_
#define _SIMD_VEC2_HPP_

#include <Math/SIMD/SIMDVector.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      class Vec2 : public SIMDVector<Vec2, 2> {
      public:
        Vec2();
        Vec2(float x, float y);

        float X() const;
        float Y() const;

        void SetX(float newX);
        void SetY(float newY);
      };
    }
  }
}
#endif