
#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#include <Math/VectorBase.hpp>

namespace jerobins {
  namespace math {

    class Vec2 : public VectorBase<Vec2> {
    public:
      Vec2();
      Vec2(float x, float y);

      float X() const;
      float Y() const;

    };
  }
}

#endif