
#ifndef _SIMD_MATRIX4_HPP_
#define _SIMD_MATRIX4_HPP_

#include <array>

#include <Common/ArgumentCheck.hpp>
#include <Math/SIMD/Vec4.hpp>

namespace jerobins {
  namespace math {
    namespace simd {
      class Matrix4 {
      public:
        /**
         * @brief Create a 4x4 matrix with all zeros.
         *
         */
        Matrix4() { /* Empty */
        }

        /**
         * @brief Create a matrix using the values from another.
         *
         * @param other The other matrix to copy values from.
         */
        Matrix4(const Matrix4 &&other) : data(other.data) { /* Empty */
        }

        /**
         * @brief Create a matrix using the values from another.
         *
         * @param other The other matrix to copy values from.
         */
        Matrix4(const Matrix4 &other) : data(other.data) { /* Empty */
        }

        /**
         * @brief Return the specified row in the matrix.
         *
         * @param row     Row index.
         * @return Vec4   Row values.
         */
        Vec4 GetRow(uint8_t row) const {
          jerobins::common::ArgumentCheck<uint8_t>(row <= 3,
                                                   "Row is out of range", row);
          return data[row];
        }

        /**
         * @brief Get the value at the specified row and column.
         *
         * @detailed Returns the value at the specified indices, throws an
         * exception if either index is out of bounds.
         *
         * @param row     The row index.
         * @param col     The column index.
         * @return float  The value at the position.
         */
        float Get(uint8_t row, uint8_t col) const {
          return GetRow(row).Get(col);
        }

        /**
         * @brief Set the value at the specified indices.
         *
         * @detailed Sets the value at the specified row and column.  Throws an
         * exception if either index is out of bounds.
         *
         * @param row     Row index.
         * @param col     Column index.
         * @param value   New value.
         */
        void Set(uint8_t row, uint8_t col, float value) {
          jerobins::common::ArgumentCheck<uint8_t>(row <= 3,
                                                   "Row is out of range", row);
          data[row].Set(col, value);
        }

        /**
         * @brief Set the values of the matrix to that of anothers.
         *
         * @param other     Matrix to copy from.
         * @return Matrix4& Return ourselves.
         */
        Matrix4 &operator=(const Matrix4 &other) {
          this->data = other.data;
          return *this;
        }

        /**
         * @brief Set the values of the matrix to that of anothers.
         *
         * @param other     Matrix to copy from.
         * @return Matrix4& Return ourselves.
         */
        Matrix4 &operator=(const Matrix4 &&other) { return *this = other; }

        /**
         * @brief Perform matrix multiplication and save the result.
         *
         * @detailed  Perform matrix multiplication as if this is the left hand
         * matrix.  The result will overwrite the current objects values.
         *
         * @param other     Other matrix.
         * @return Matrix4& Result.
         */
        Matrix4 &operator*=(const Matrix4 &other) {
          Matrix4 trans = other.Transpose();
          for (int row = 0; row < 4; ++row) {
            Vec4 tmp;
            for (uint8_t col = 0; col < 4; ++col) {
              tmp += data[row] * trans.GetRow(col);
            }
            data[row] = tmp;
          }
          return *this;
        }

        /**
         * @brief Perform matrix multiplication and save the result.
         *
         * @detailed  Perform matrix multiplication as if this is the left hand
         * matrix.  The result will overwrite the current objects values.
         *
         * @param other     Other matrix.
         * @return Matrix4& Result.
         */
        Matrix4 &operator*=(const Matrix4 &&other) {
          return this->operator*=(other);
        }

        /**
         * @brief Perform matrix multiplication and return the result.
         *
         * @detailed  Perform matrix multiplication as if this is the left hand
         * matrix.  The result will be a new matrix.
         *
         * @param other     Other matrix.
         * @return Matrix4& Result.
         */
        Matrix4 operator*(const Matrix4 &other) const {
          Matrix4 result(*this);
          result *= other;
          return result;
        }

        /**
         * @brief Perform matrix multiplication and return the result.
         *
         * @detailed  Perform matrix multiplication as if this is the left hand
         * matrix.  The result will be a new matrix.
         *
         * @param other     Other matrix.
         * @return Matrix4& Result.
         */
        Matrix4 operator*(const Matrix4 &&other) const { return *this * other; }

        Vec4 operator*(const Vec4 &&other) const {
          Vec4 result;
          for (uint8_t row = 0; row < 4; ++row) {
            result.Set(row, data[row].Dot(other));
          }
          return result;
        }

        /**
         * @brief Transpose the matrix.
         *
         * @return Matrix4  Return a new matrix.
         */
        Matrix4 Transpose() const {
          Matrix4 result(*this);
          _MM_TRANSPOSE4_PS(result.data[0].RawSIMD(), result.data[1].RawSIMD(),
                            result.data[2].RawSIMD(), result.data[3].RawSIMD());
          return result;
        }

      private:
        std::array<Vec4, 4> data;
      };
    } // namespace simd
  }   // namespace math
} // namespace jerobins
#endif