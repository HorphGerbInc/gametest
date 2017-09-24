
#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {
    template <typename ElementType = float>
    class Vec3 : public ArrayVector<Vec3<ElementType>, 3, ElementType> {
    public:
      Vec3() : Vec3(0, 0, 0) {}
      
      Vec3(ElementType x, ElementType y, ElementType z) {
        SetX(x);
        SetX(y);
        SetX(z);
      }

      ElementType X() const { return this->Get(0); }
      ElementType Y() const { return this->Get(1); }
      ElementType Z() const { return this->Get(2); }

      void SetX(ElementType value) { this->Set(0, value); }
      void SetY(ElementType value) { this->Set(1, value); }
      void SetZ(ElementType value) { this->Set(2, value); }

      // Cross Product
      Vec3 Cross(const Vec3 &&other) const {
        ElementType x;
        ElementType y;
        ElementType z;
        return Vec3(x, y, z);
      }
    };
  }
}

#endif