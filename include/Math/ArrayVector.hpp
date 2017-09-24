
#ifndef _VECTORARRAY_HPP_
#define _VECTORARRAY_HPP_

#include <Math/VectorBase.hpp>

namespace jerobins {
  namespace math {

    template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

    template <class DerivedClass, int Dim, typename ElementType>
    class ArrayVector : public VectorBase<DerivedClass, Dim, ElementType> {

    public:
      template <size_t D1 = Dim, EnableIfB<D1 == 2> = 0>
      ArrayVector(ElementType x = 0, ElementType y = 0) {
        Set(0, x);
        Set(1, y);
      }

      template <size_t D1 = Dim, EnableIfB<D1 == 3> = 0>
      ArrayVector(ElementType x = 0, ElementType y = 0, ElementType z = 0) {
        Set(0, x);
        Set(1, y);
        Set(2, z);
      }
      template <size_t D1 = Dim, EnableIfB<D1 == 4> = 0>
      ArrayVector(ElementType x = 0, ElementType y = 0, ElementType z = 0, ElementType w = 0) {
        Set(0, x);
        Set(1, y);
        Set(2, z);
        Set(3, w);
      }
      // Pairwise Multiplication
      virtual DerivedClass &operator*=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) * other.Get(i));
        }
        return this->CastToDerived();
      }

      // Pairwise Addition
      virtual DerivedClass &operator+=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) + other.Get(i));
        }
        return this->CastToDerived();
      }

      // Pairwise Subtraction
      virtual DerivedClass &operator-=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) - other.Get(i));
        }
        return this->CastToDerived();
      }

      // Scalar multiplication
      virtual DerivedClass &operator*=(const ElementType &scalar) {
        for (int i = 0; i < Dim; ++i) {
          Set(i, Get(i) * scalar);
        }
        return this->CastToDerived();
      }

      virtual ElementType Dot(const DerivedClass &other) const {
        ElementType result = 0;
        for (int i = 0; i < Dim; ++i) {
          result += this->Get(i) * other.Get(i);
        }
        return result;
      }

      virtual ElementType Get(int i) const {
        this->BoundsCheck(i);
        return data_[i];
      }

      virtual void Set(int pos, ElementType value) {
        this->BoundsCheck(pos);
        data_[pos] = value;
      }

      virtual const ElementType *Raw() const { return data_; }

    private:
      ElementType data_[Dim];
    };
  }
}

#endif