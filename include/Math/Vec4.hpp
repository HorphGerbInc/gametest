
#ifndef _VEC4_HPP_
#define _VEC4_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {

    /**
     * @brief Four dimensional vector.
     *
     * @tparam ElementType Element types of the vector.
     */
    template <typename ElementType = float>
    class Vec4 : public ArrayVector<Vec4<ElementType>, 4, ElementType> {
    public:
      /**
       * @brief Creates the zero vector.
       *
       */
      Vec4() : Vec4(0, 0, 0, 0) {}

      /**
       * @brief Creates a vector with the given values.
       *
       * @param x X value.
       * @param y Y value.
       * @param z Z value.
       * @param w W value.
       */
      Vec4(ElementType x, ElementType y, ElementType z, ElementType w) {
        SetX(x);
        SetY(y);
        SetZ(z);
        SetW(w);
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
       * @brief Get the Z value.
       *
       * @return ElementType Z value.
       */
      ElementType Z() const { return this->Get(2); }

      /**
       * @brief Get the W value.
       *
       * @return ElementType W value.
       */
      ElementType W() const { return this->Get(3); }

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

      /**
       * @brief Set the Z value.
       *
       * @param value New value.
       */
      void SetZ(ElementType value) { this->Set(2, value); }

      /**
       * @brief Set the W value.
       *
       * @param value New value.
       */
      void SetW(ElementType value) { this->Set(3, value); }
    };
  } // namespace math
} // namespace jerobins

#endif