
#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <Math/ArrayVector.hpp>

namespace jerobins {
  namespace math {
    /**
     * @brief
     *
     * @tparam float
     */
    template <typename ElementType = float>
    class Vec3 : public ArrayVector<Vec3<ElementType>, 3, ElementType> {
    public:
      /**
       * @brief Create the zero vector.
       *
       */
      Vec3() : Vec3(0, 0, 0) {}

      /**
       * @brief Create a vector with the given values.
       *
       * @param x X value.
       * @param y Y value.
       * @param z Z value.
       */
      Vec3(ElementType x, ElementType y, ElementType z) {
        SetX(x);
        SetY(y);
        SetZ(z);
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
       * @brief Return the cross product.
       *
       * @param other Right hand side of cross product.
       * @return Vec3 Cross product.
       */
      Vec3 Cross(const Vec3 &&other) const {
        ElementType x;
        ElementType y;
        ElementType z;
        return Vec3(x, y, z);
      }
    };
  } // namespace math
} // namespace jerobins

#endif