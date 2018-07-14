
#ifndef _VECTORARRAY_HPP_
#define _VECTORARRAY_HPP_

#include <Math/VectorBase.hpp>

namespace jerobins {
  namespace math {

    template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

    // Array based vector class
    template <class DerivedClass, int Dim, typename ElementType>
    class ArrayVector : public VectorBase<DerivedClass, Dim, ElementType> {

    public:
      /**
       * @brief Create a two dimensional array vector.
       *
       * @param x X value.
       * @param y Y value.
       */
      template <size_t D1 = Dim, EnableIfB<D1 == 2> = 0>
      ArrayVector(ElementType x = 0, ElementType y = 0) {
        Set(0, x);
        Set(1, y);
      }

      /**
       * @brief Create a three dimensional array vector.
       *
       * @param x X value.
       * @param y Y value.
       * @param z Z value.
       */
      template <size_t D1 = Dim, EnableIfB<D1 == 3> = 0>
      ArrayVector(ElementType x = 0, ElementType y = 0, ElementType z = 0) {
        Set(0, x);
        Set(1, y);
        Set(2, z);
      }

      /**
       * @brief Create a four dimensional array vector.
       *
       * @param x X value.
       * @param y Y value.
       * @param z Z value.
       * @param w W value.
       */
      template <size_t D1 = Dim, EnableIfB<D1 == 4> = 0>
      ArrayVector(ElementType x = 0, ElementType y = 0, ElementType z = 0,
                  ElementType w = 0) {
        Set(0, x);
        Set(1, y);
        Set(2, z);
        Set(3, w);
      }

      /**
       * @brief Performs pairwise multiplication and saves the result.
       *
       * @param other           The other vector.
       * @return DerivedClass&  Myself.
       */
      virtual DerivedClass &operator*=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) * other.Get(i));
        }
        return this->CastToDerived();
      }

      /**
       * @brief Performs pairwise addition and saves the result.
       *
       * @param other           The other vector.
       * @return DerivedClass&  Myself.
       */
      virtual DerivedClass &operator+=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) + other.Get(i));
        }
        return this->CastToDerived();
      }

      /**
       * @brief Performs pairwise subtraction and saves the result.
       *
       * @param other           The other vector.
       * @return DerivedClass&  Myself.
       */
      virtual DerivedClass &operator-=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) - other.Get(i));
        }
        return this->CastToDerived();
      }

      /**
       * @brief Performs scalar multiplication and saves the result.
       *
       * @param other           Scalar value.
       * @return DerivedClass&  Myself.
       */
      virtual DerivedClass &operator*=(const ElementType &scalar) {
        for (int i = 0; i < Dim; ++i) {
          Set(i, Get(i) * scalar);
        }
        return this->CastToDerived();
      }

      /**
       * @brief Perform dot product.
       *
       * @param other         Other vector.
       * @return ElementType  The dot product.
       */
      virtual ElementType Dot(const DerivedClass &other) const {
        ElementType result = 0;
        for (int i = 0; i < Dim; ++i) {
          result += this->Get(i) * other.Get(i);
        }
        return result;
      }

      /**
       * @brief Get the value at the given index.
       *
       * @param pos           Vector index
       * @return ElementType  Value at the index.
       */
      virtual ElementType Get(int pos) const {
        this->BoundsCheck(pos);
        return data_[pos];
      }

      /**
       * @brief Set the value at the given index.
       *
       * @param pos   Vector index.
       * @param value New value.
       */
      virtual void Set(int pos, ElementType value) {
        this->BoundsCheck(pos);
        data_[pos] = value;
      }

      /**
       * @brief Get the raw underlying array.
       *
       * @return const ElementType* Underlying array.
       */
      virtual const ElementType *Raw() const { return data_; }

    private:
      ElementType data_[Dim];
    };
  } // namespace math
} // namespace jerobins

#endif