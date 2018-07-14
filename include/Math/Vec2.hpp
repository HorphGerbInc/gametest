
#ifndef _VEC2_HPP_
#define _VEC2_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {

    /**
     * @brief Two dimensional vector.
     *
     * @tparam ElementType  Type of elements in the vector.
     */
    template <typename ElementType = float>
    class Vec2 : public ArrayVector<Vec2<ElementType>, 2, ElementType> {
    public:
          /**
       * @brief Zero vector.
       *
       */
      Vec2() : Vec2(0, 0) {}

      /**
       * @brief Vector with given values.
       *
       * @param x   X value.
       * @param y   Y value.
       */
      Vec2(ElementType x, ElementType y) {
        SetX(x);
        SetY(y);
      }

      /**
       * @brief Get the X value.
       *
       * @return ElementType X value.
       */
      ElementType X() const { return this->Get(0); }

      /**
       * @brief Get the Y value.
       *
       * @return ElementType Y value.
       */
      ElementType Y() const { return this->Get(1); }

      /**
       * @brief Set the X value.
       *
       * @param value New value.
       */
      void SetX(ElementType value) { this->Set(0, value); }

      /**
       * @brief Set the Y value.
       *
       * @param value New value.
       */
      void SetY(ElementType value) { this->Set(1, value); }
    };
  } // namespace math
} // namespace jerobins

#endif