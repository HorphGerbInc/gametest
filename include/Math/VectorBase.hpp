
#ifndef _VECTORBASE_HPP_
#define _VECTORBASE_HPP_

#include <stdexcept>

namespace jerobins {
  namespace math {

    template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

    template <class DerivedClass, int Dim> class VectorBase {
    public:
      template <size_t D1 = Dim, EnableIfB<D1 == 2> = 0>
      VectorBase(float x = 0, float y = 0) {
        Set(0, x);
        Set(1, y);
      }

      template <size_t D1 = Dim, EnableIfB<D1 == 3> = 0>
      VectorBase(float x = 0, float y = 0, float z = 0) {
        Set(0, x);
        Set(1, y);
        Set(2, z);
      }

      template <size_t D1 = Dim, EnableIfB<D1 == 4> = 0>
      VectorBase(float x = 0, float y = 0, float z = 0, float w = 0) {
        Set(0, x);
        Set(1, y);
        Set(2, z);
        Set(3, w);
      }

      DerivedClass &operator=(const DerivedClass &other) {
        for (int i = 0; i < Dim; ++i)
          Set(i, other.Get(i));
        return CastToDerived();
      }
      DerivedClass &operator=(const DerivedClass &&other) {
        for (int i = 0; i < Dim; ++i)
          Set(i, other.Get(i));
        return CastToDerived();
      }
      // Pairwise multiplication
      virtual DerivedClass &operator*=(const DerivedClass &other) = 0;

      DerivedClass &operator*=(const DerivedClass &&other) {
        return *this *= other;
      }

      DerivedClass operator*(const DerivedClass &other) const {
        DerivedClass result;
        for (int i = 0; i < Dim; ++i) {
          result.Set(i, Get(i));
        }
        result *= other;
        return result;
      }

      DerivedClass operator*(const DerivedClass &&other) const {
        return *this * other;
      }

      // Scalar multiplication
      virtual DerivedClass &operator*=(const float &scalar) = 0;

      DerivedClass &operator*=(const float &&scalar) {
        return (*this *= scalar);
      }

      DerivedClass operator*(const float &scalar) {
        DerivedClass result(*this);
        return result *= scalar;
      }

      DerivedClass operator*(const float &&scalar) { return *this * scalar; }

      // Pairwise Addition
      virtual DerivedClass &operator+=(const DerivedClass &other) = 0;

      DerivedClass &operator+=(const DerivedClass &&other) {
        return *this += other;
      }

      DerivedClass operator+(const DerivedClass &other) const {
        DerivedClass result = Clone();
        result += other;
        return result;
      }

      DerivedClass operator+(const DerivedClass &&other) const {
        return *this + other;
      }

      // Pairwise Subtraction
      virtual DerivedClass &operator-=(const DerivedClass &other) = 0;

      DerivedClass &operator-=(const DerivedClass &&other) {
        return *this -= other;
      }

      DerivedClass operator-(const DerivedClass &other) const {
        DerivedClass result = Clone();
        result -= other;
        return result;
      }

      DerivedClass operator-(const DerivedClass &&other) const {
        return (*this - other);
      }

      // Dot
      virtual float Dot(const DerivedClass &other) const = 0;

      float Dot(const DerivedClass &&other) const { return Dot(other); }

      // Mutators
      virtual float Get(int) const = 0;
      virtual void Set(int, float) = 0;

      virtual const float *Raw() const = 0;

    protected:
      void BoundsCheck(int pos) const {
        if (pos < 0 || pos > Dim) {
          throw std::runtime_error("Out of bounds");
        }
      }

      DerivedClass &CastToDerived() {
        return *static_cast<DerivedClass *>(this);
      }

      const DerivedClass &CastToDerived() const {
        return *static_cast<DerivedClass *>(this);
      }

    private:
      DerivedClass Clone() const {
        DerivedClass result;
        for (int i = 0; i < Dim; ++i)
          result.Set(i, Get(i));
        return result;
      }
    };
  }
}

#endif