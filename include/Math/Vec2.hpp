
#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {

    class Vec2 : public ArrayVector<Vec2,2> {
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

#endif