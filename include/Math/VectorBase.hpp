
#ifndef _VECTORBASE_HPP_
#define _VECTORBASE_HPP_

#ifdef WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

namespace jerobins {
  namespace math {

    template <class DerivedClass> class VectorBase {

    public:
      VectorBase() {
        this->data_[0] = 0;
        this->data_[1] = 0;
        this->data_[2] = 0;
        this->data_[3] = 0;
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

      // Addition
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
        return *this += other;
      }

      // Dot
      float Dot(const VectorBase &&other) const {
        return _mm_dp_ps(xmm_, other.xmm_, 15)[0];
      }

      float Dot(const VectorBase &other) const {
        float data[4];
        auto result = _mm_dp_ps(xmm_, other.xmm_, 15);
        _mm_storeu_ps(data, result);
        return data[0];
      }

    protected:
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