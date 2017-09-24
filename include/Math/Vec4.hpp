
#ifndef _VEC4_HPP_
#define _VEC4_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {

    template <typename ElementType = float>
    class Vec4 : public ArrayVector<Vec4<ElementType>, 4, ElementType> {
    public:
      Vec4() : Vec4(0, 0, 0, 0) {}
      Vec4(ElementType x, ElementType y, ElementType z, ElementType w) {
        SetX(x);
        SetY(y);
        SetZ(z);
        SetW(w);
      }

      ElementType X() const { return this->Get(0); }
      ElementType Y() const { return this->Get(1); }
      ElementType Z() const { return this->Get(2); }
      ElementType W() const { return this->Get(3); }

      void SetX(ElementType value) { this->Set(0, value); }
      void SetY(ElementType value) { this->Set(1, value); }
      void SetZ(ElementType value) { this->Set(2, value); }
      void SetW(ElementType value) { this->Set(3, value); }
    };
  }
}

#endif