

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
      /**
       * @brief SIMD based vector class.
       *
       * @tparam DerivedClass   The class which has SIMDVector as it's base
       * class.
       * @tparam Dim            The number of dimesions.
       */
      template <class DerivedClass, int Dim>
      class SIMDVector : public VectorBase<DerivedClass, Dim, float> {

      public:
        /**
         * @brief SIMD vector when the number of dimensions is 2.
         *
         * @param x Value of the x component.
         * @param y Value of the y component.
         */
        template <size_t D1 = Dim, EnableIfB<D1 == 2> = 0>
        SIMDVector(float x = 0, float y = 0) {
          Set(0, x);
          Set(1, y);
        }

        /**
         * @brief SIMD vector when the number of dimensions is 3.
         *
         * @param x Value of the x component.
         * @param y Value of the y component.
         * @param z Value of the z component.
         */
        template <size_t D1 = Dim, EnableIfB<D1 == 3> = 0>
        SIMDVector(float x = 0, float y = 0, float z = 0) {
          Set(0, x);
          Set(1, y);
          Set(2, z);
        }

        /**
         * @brief SIMD vector when the number of dimensions is 4.
         *
         * @param x Value of the x component.
         * @param y Value of the y component.
         * @param z Value of the z component.
         * @param w Value of the w component.
         */
        template <size_t D1 = Dim, EnableIfB<D1 == 4> = 0>
        SIMDVector(float x = 0, float y = 0, float z = 0, float w = 0) {
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
          xmm_ = _mm_mul_ps(this->xmm_, other.xmm_);
          return this->CastToDerived();
        }

        /**
         * @brief Performs scalar multiplication and saves the result.
         *
         * @param scalar          Scalar value.
         * @return DerivedClass&  Myself.
         */
        virtual DerivedClass &operator*=(const float &scalar) {
          __m128 scalarVector = _mm_set1_ps(scalar);
          this->xmm_ = _mm_mul_ps(this->xmm_, scalarVector);
          return this->CastToDerived();
        }

        /**
         * @brief Performs pairwise addition and saves the result.
         *
         * @param other           The other vector.
         * @return DerivedClass&  Myself.
         */
        virtual DerivedClass &operator+=(const DerivedClass &other) {
          xmm_ = _mm_add_ps(this->xmm_, other.xmm_);
          return this->CastToDerived();
        }

        /**
         * @brief Performs pairwise subtraction and saves the result.
         *
         * @param other           The other vector.
         * @return DerivedClass&  Myself.
         */
        virtual DerivedClass &operator-=(const DerivedClass &other) {
          this->xmm_ = _mm_sub_ps(this->xmm_, other.xmm_);
          return this->CastToDerived();
        }

        /**
         * @brief Performs dot product.
         *
         * @param other     The other vector.
         * @return float    Dot product.
         */
        virtual float Dot(const DerivedClass &other) const {
          float data[4];
          auto result = _mm_dp_ps(xmm_, other.xmm_, 255);
          _mm_storeu_ps(data, result);
          return data[0];
        }

        /**
         * @brief Returns the raw pointer to the data.
         *
         * @return const float* Pointer to data.
         */
        virtual const float *Raw() const { return data_; }

        /**
         * @brief Return the value at the given index.
         *
         * @detailed Returns the value at the given index.  Throws an exception
         * if the index is out of bounds.
         *
         * @param pos     Vector index.
         * @return float  Value at index.
         */
        virtual float Get(int pos) const {
          this->BoundsCheck(pos);
          return data_[pos];
        }

        /**
         * @brief Set the value at the given index.
         *
         * @detailed Sets the value at the given index.  Throws an exception
         * if the index is out of bounds.
         *
         * @param pos     Vector index.
         * @return value  New value.
         */
        virtual void Set(int pos, float value) {
          this->BoundsCheck(pos);
          data_[pos] = value;
        }

        /**
         * @brief Return the SIMD struct.
         *
         * @return __m128 The SIMD struct.
         */
        __m128 RawSIMD() const { return xmm_; }

      private:
        union {
          __m128 xmm_;
          float data_[4];
        };
      };
    } // namespace simd
  }   // namespace math
} // namespace jerobins

#endif