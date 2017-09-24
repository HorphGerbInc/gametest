

#ifndef _SIMD_VECTORBASE_HPP_
#define _SIMD_VECTORBASE_HPP_

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#include <Math/VectorBase.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

      template <class DerivedClass, int Dim>
      class SIMDVector : public VectorBase<DerivedClass, Dim> {

      public:
        template <size_t D1 = Dim, EnableIfB<D1 == 2> = 0>
        SIMDVector(float x = 0, float y = 0)  {
          Set(0, x);
          Set(1, y);
        }
  
        template <size_t D1 = Dim, EnableIfB<D1 == 3> = 0>
        SIMDVector(float x = 0, float y = 0, float z = 0) {
          Set(0, x);
          Set(1, y);
          Set(2, z);
        }
        template <size_t D1 = Dim, EnableIfB<D1 == 4> = 0>
        SIMDVector(float x = 0, float y = 0, float z = 0, float w = 0) {
          Set(0, x);
          Set(1, y);
          Set(2, z);
          Set(3, w);
        }
        // Pairwise multiplication
        virtual DerivedClass &operator*=(const DerivedClass &other) {
          xmm_ = _mm_mul_ps(this->xmm_, other.xmm_);
          return CastToDerived();
        }

        // Scalar multiplication
        virtual DerivedClass &operator*=(const float &scalar) {
          __m128 scalarVector = _mm_set1_ps(scalar);
          this->xmm_ = _mm_mul_ps(this->xmm_, scalarVector);
          return CastToDerived();
        }

        // Pairwise Addition
        virtual DerivedClass &operator+=(const DerivedClass &other) {
          xmm_ = _mm_add_ps(this->xmm_, other.xmm_);
          return CastToDerived();
        }

        // Pairwise Subtraction
        virtual DerivedClass &operator-=(const DerivedClass &other) {
          this->xmm_ = _mm_sub_ps(this->xmm_, other.xmm_);
          return CastToDerived();
        }

        // Dot
        virtual float Dot(const DerivedClass &other) const {
          float data[4];
          auto result = _mm_dp_ps(xmm_, other.xmm_, 255);
          _mm_storeu_ps(data, result);
          return data[0];
        }

        virtual const float *Raw() const { return data_; }

        virtual float Get(int pos) const {
          BoundsCheck(pos);
          return data_[pos];
        }

        virtual void Set(int pos, float value) {
          BoundsCheck(pos);
          data_[pos] = value;
        }

        __m128 RawSIMD() const { return xmm_; }

      private:
        union {
          __m128 xmm_;
          float data_[4];
        };
      };
    }
  }
}

#endif