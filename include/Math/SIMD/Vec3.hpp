
#ifndef _SIMD_VEC3_HPP_
#define _SIMD_VEC3_HPP_

#include <Math/SIMD/SIMDVector.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      /**
       * @brief A three dimensional vector using SIMD.
       *
       */
      class Vec3 : public SIMDVector<Vec3, 3> {
      public:
        /**
         * @brief Creates a zero vector.
         *
         */
        Vec3();

        /**
         * @brief Create a vector with the given values.
         *
         * @param x The X value.
         * @param y The Y value.
         * @param z The Z value.
         */
        Vec3(float x, float y, float z);

        /**
         * @brief Return the X value.
         *
         * @return float  The X value.
         */
        float X() const;

        /**
         * @brief Return the Y value.
         *
         * @return float  The T value.
         */
        float Y() const;

        /**
         * @brief Return the Z value.
         *
         * @return float  The Z value.
         */
        float Z() const;

        /**
         * @brief Set the X value.
         *
         * @param newX  New value.
         */
        void SetX(float newZ);

        /**
         * @brief Set the Y value.
         *
         * @param newY  New value.
         */
        void SetY(float newY);

        /**
         * @brief Set the Z value.
         *
         * @param newZ New value.
         */
        void SetZ(float newZ);

        /**
         * @brief Perform the cross product.
         *
         * @param other   Other vector.
         * @return Vec3   The cross product.
         */
        Vec3 Cross(const Vec3 &&other) const;
      };
    } // namespace simd
  }   // namespace math
} // namespace jerobins

#endif