
#ifndef _MATRIX4_HPP_
#define _MATRIX4_HPP_

#include <array>

#include <Common/ArgumentCheck.hpp>
#include <Math/Vec4.hpp>

namespace jerobins {
  namespace math {

    // 4x4 Matrix class
    class Matrix4 {
    public:
      /**
       * @brief Create a matrix of zeroes.
       *
       */
      Matrix4() { /* Empty */
      }

      /**
       * @brief Create a matrix from another matrix.
       *
       * @param other Matrix we copy from.
       */
      Matrix4(const Matrix4 &&other) : data(other.data) { /* Empty */
      }

      /**
       * @brief Create a matrix from another matrix.
       *
       * @param other Matrix we copy from.
       */
      Matrix4(const Matrix4 &other) : data(other.data) { /* Empty */
      }

      /**
       * @brief Get the specified row.
       *
       * @param row     Row index.
       * @return Vec4<> The row.
       */
      Vec4<> GetRow(uint8_t row) const {
        jerobins::common::ArgumentCheck<uint8_t>(row <= 3,
                                                 "Row is out of range", row);
        return data[row];
      }

      /**
       * @brief Return the element at the specified indices.
       *
       * @param row     Row index.
       * @param col     Column index.
       * @return float  Value at the given position.
       */
      float Get(uint8_t row, uint8_t col) const { return GetRow(row).Get(col); }

      /**
       * @brief Set the value at the specified position.
       *
       * @param row   Row index.
       * @param col   Column index.
       * @param value New value.
       */
      void Set(uint8_t row, uint8_t col, float value) {
        jerobins::common::ArgumentCheck<uint8_t>(row <= 3,
                                                 "Row is out of range", row);
        data[row].Set(col, value);
      }

      /**
       * @brief Set our matrix values to the values of the other matrix.
       *
       * @param other       Right hand side.
       * @return Matrix4&   This matrix.
       */
      Matrix4 &operator=(const Matrix4 &other) {
        this->data = other.data;
        return *this;
      }

      /**
       * @brief Set our matrix values to the values of the other matrix.
       *
       * @param other       Right hand side.
       * @return Matrix4&   This matrix.
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
          Vec4<> tmp;
          for (uint8_t col = 0; col < 4; ++col) {
            tmp += data[row] * trans.GetRow(col);
          }
          data[row] = tmp;
        }
        return *this;
      }

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

      Vec4<> operator*(const Vec4<> &&other) const {
        Vec4<> result;
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
        Matrix4 result;
        for (int row = 0; row < 4; ++row) {
          for (int col = 0; col < 4; ++col) {
            result.Set(row, col, Get(col, row));
          }
        }
        return result;
      }

    private:
      std::array<Vec4<float>, 4> data;
    };
  } // namespace math
} // namespace jerobins

#endif