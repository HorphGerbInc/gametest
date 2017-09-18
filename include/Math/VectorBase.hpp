
#ifndef _VECTORBASE_HPP_
#define _VECTORBASE_HPP_

#include <stdexcept>

#ifdef WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

namespace jerobins {
  namespace math {

    template <class DerivedClass> class VectorBase {

    public:
      VectorBase(int dim, float x = 0, float y = 0, float z = 0, float w = 0)
          : dim(dim) {
        this->data_[0] = x;
        this->data_[1] = y;
        this->data_[2] = z;
        this->data_[3] = w;
      }

      VectorBase(const DerivedClass &other) {
        for (int i = 0; i < dim; ++i) {
          Set(i, other.Get(i));
        }
      }

      VectorBase(const DerivedClass &&other) : VectorBase(other) { /* Empty */
      }

      DerivedClass &operator=(const DerivedClass &other) {
        this->xmm_ = other.xmm_;
        return *this;
      }

      DerivedClass &operator=(const DerivedClass &&other) {
        return *this = other;
      }

      // Pairwise multiplication
      DerivedClass &operator*=(const DerivedClass &other) {
        xmm_ = _mm_mul_ps(this->xmm_, other.xmm_);
        return CastToDerived();
      }

      DerivedClass &operator*=(const DerivedClass &&other) {
        return *this *= other;
      }

      DerivedClass operator*(const DerivedClass &other) const {
        DerivedClass result;
        result.xmm_ = _mm_mul_ps(this->xmm_, other.xmm_);
        return result;
      }

      DerivedClass operator*(const DerivedClass &&other) const {
        return *this * other;
      }

      // Scalar multiplication
      DerivedClass &operator*=(const float &scalar) {
        __m128 scalarVector = _mm_set1_ps(scalar);
        this->xmm_ = _mm_mul_ps(this->xmm_, scalarVector);
        return CastToDerived();
      }

      DerivedClass &operator*=(const float &&scalar) {
        return (*this *= scalar);
      }

      DerivedClass operator*(const float &scalar) {
        DervicedClass result(*this);
        return result *= scalar;
      }

      DerivedClass operator*(const float &&scalar) { return *this * scalar; }

      // Pairwise Addition
      DerivedClass &operator+=(const DerivedClass &other) {
        xmm_ = _mm_add_ps(this->xmm_, other.xmm_);
        return CastToDerived();
      }

      DerivedClass &operator+=(const DerivedClass &&other) {
        return *this += other;
      }

      DerivedClass operator+(const DerivedClass &other) const {
        DerivedClass result;
        result.xmm_ = _mm_add_ps(this->xmm_, other.xmm_);
        return result;
      }

      DerivedClass operator+(const DerivedClass &&other) const {
        return *this + other;
      }

      // Pairwise Subtraction
      DerivedClass &operator-=(const DerivedClass &other) {
        this->xmm_ = _mm_sub_ps(this->xmm_, other.xmm_);
        return CastToDerived();
      }

      DerivedClass &operator-=(const DerivedClass &&other) {
        return *this -= other;
      }

      DerivedClass operator-(const DerivedClass &other) const {
        DerivedClass result;
        result.xmm_ = _mm_sub_ps(this->xmm_, other.xmm_);
        return result;
      }

      DerivedClass operator-(const DerivedClass &&other) const {
        return (*this - other);
      }

      // Dot
      float Dot(const VectorBase &&other) const {
		  return Dot(other);
      }

      float Dot(const VectorBase &other) const {
        float data[4];
        auto result = _mm_dp_ps(xmm_, other.xmm_, 255);
        _mm_storeu_ps(data, result);
        return data[0];
      }

      float Get(int pos) const {
        if (pos < 0 || pos > 3) {
          throw std::runtime_error("Out of bounds");
        }
        return data_[pos];
      }

      void Set(int pos, float value) {
        if (pos < 0 || pos > 3) {
          throw std::runtime_error("Out of bounds");
        }
        data_[pos] = value;
      }

    protected:
      int dim;
      union {
        __m128 xmm_;
        float data_[4];
      };

    private:
      DerivedClass &CastToDerived() {
        return *static_cast<DerivedClass *>(this);
      }
    };
  }
}

#endif