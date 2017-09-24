
#ifndef _VECTORARRAY_HPP_
#define _VECTORARRAY_HPP_

#include <Math/VectorBase.hpp>

namespace jerobins {
  namespace math {

    template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

    template <class DerivedClass, int Dim>
    class ArrayVector : public VectorBase<DerivedClass, Dim> {

    public:
      template <size_t D1 = Dim, EnableIfB<D1 == 2> = 0>
      ArrayVector(float x = 0, float y = 0) {
        Set(0, x);
        Set(1, y);
      }

      template <size_t D1 = Dim, EnableIfB<D1 == 3> = 0>
      ArrayVector(float x = 0, float y = 0, float z = 0) {
        Set(0, x);
        Set(1, y);
        Set(2, z);
      }
      template <size_t D1 = Dim, EnableIfB<D1 == 4> = 0>
      ArrayVector(float x = 0, float y = 0, float z = 0, float w = 0) {
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
        return CastToDerived();
      }

      // Pairwise Addition
      virtual DerivedClass &operator+=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) + other.Get(i));
        }
        return CastToDerived();
      }

      // Pairwise Subtraction
      virtual DerivedClass &operator-=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i) {
          this->Set(i, Get(i) - other.Get(i));
        }
        return CastToDerived();
      }

      // Scalar multiplication
      virtual DerivedClass &operator*=(const float &scalar) {
        for (int i = 0; i < Dim; ++i) {
          Set(i, Get(i) * scalar);
        }
        return CastToDerived();
      }

      virtual float Dot(const DerivedClass &other) const {
        float result = 0;
        for (int i = 0; i < Dim; ++i) {
          result += this->Get(i) * other.Get(i);
        }
        return result;
      }

      virtual float Get(int i) const {
        BoundsCheck(i);
        return data_[i];
      }

      virtual void Set(int pos, float value) {
        BoundsCheck(pos);
        data_[pos] = value;
      }

      virtual const float *Raw() const { return data_; }

    private:
      float data_[Dim];
    };
  }
}

#endif