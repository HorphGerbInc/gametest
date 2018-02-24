
#ifndef _SIMD_VEC2_HPP_
#define _SIMD_VEC2_HPP_

#include <Math/SIMD/SIMDVector.hpp>

namespace jerobins {
  namespace math {
    namespace simd {

      /**
       * @brief A two dimensional vector using SIMD.
       *
       */
      class Vec2 : public SIMDVector<Vec2, 2> {
      public:
        /**
         * @brief Creates a zero vector.
         *
         */
        Vec2();

        /**
         * @brief Create a vector with the given values.
         *
         * @param x The X value.
         * @param y The Y value.
         */
        Vec2(float x, float y);

        /**
         * @brief Return the X value.
         *
         * @return float  The X value.
         */
        float X() const;

        /**
         * @brief Return the Y value.
         *
         * @return float  The Y value.
         */
        float Y() const;

        /**
         * @brief Set the X value.
         *
         * @param newX  New value.
         */
        void SetX(float newX);

        /**
         * @brief Set the Y value.
         *
         * @param newY  New value.
         */
        void SetY(float newY);
      };
    } // namespace simd
  }   // namespace math
} // namespace jerobins
#endif