
#ifndef _SIMD_VEC4_HPP_
#define _SIMD_VEC4_HPP_

#include <Math/SIMD/SIMDVector.hpp>

namespace jerobins {
  namespace math {
    namespace simd {
      /**
       * @brief A four dimensional vector using SIMD.
       *
       */
      class Vec4 : public SIMDVector<Vec4, 4> {
      public:
        /**
         * @brief Creates a zero vector.
         *
         */
        Vec4();

        /**
         * @brief Create a vector with the given values.
         *
         * @param x The X value.
         * @param y The Y value.
         * @param z The Z value.
         * @param w The W value.
         */
        Vec4(float x, float y, float z, float w);

        /**
         * @brief Returns the X value.
         *
         * @return float X value.
         */
        float X() const;

        /**
         * @brief Returns the Y value.
         *
         * @return float Y value.
         */
        float Y() const;

        /**
         * @brief Returns the Z value.
         *
         * @return float Z value.
         */
        float Z() const;

        /**
         * @brief Returns the W value.
         *
         * @return float W value.
         */
        float W() const;

        /**
         * @brief Sets the X value.
         *
         * @param newX  New value.
         */
        void SetX(float newX);

        /**
         * @brief Sets the Y value.
         *
         * @param newY  New value.
         */
        void SetY(float newY);

        /**
         * @brief Sets the Z value.
         *
         * @param newZ  New value.
         */
        void SetZ(float newZ);

        /**
         * @brief Sets the W value.
         *
         * @param newW  New value.
         */
        void SetW(float newW);
      };
    } // namespace simd
  }   // namespace math
} // namespace jerobins

#endif