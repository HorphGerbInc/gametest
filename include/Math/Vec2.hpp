
#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {

    template <typename ElementType = float>
    class Vec2 : public ArrayVector<Vec2<ElementType>, 2, ElementType> {
    public:
      Vec2() : Vec2(0, 0) {}
      Vec2(ElementType x, ElementType y) {
        SetX(x);
        SetY(y);
      }

      ElementType X() const { return this->Get(0); }
      ElementType Y() const { return this->Get(1); }

      void SetX(ElementType value) { this->Set(0, value); }
      void SetY(ElementType value) { this->Set(1, value); }
    };
  }
}

#endif