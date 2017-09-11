
#ifndef _MATRIX4_HPP_
#define _MATRIX4_HPP_

#include <array>

#ifdef WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#include <Common/ArgumentCheck.hpp>
#include <Math/Vec4.hpp>

namespace jerobins {
  namespace math {
    class Matrix4 {
    public:
      // Create the 0 matrix
      Matrix4() { /* Empty */
      }

      // Copy
      Matrix4(const Matrix4 &&other) : data(other.data) { /* Empty */ }

      Matrix4(const Matrix4 &other) : data(other.data) { /* Empty */ }

      Vec4 GetRow(uint8_t row) const {
        jerobins::common::ArgumentCheck<uint8_t>(row <= 3,
                                                 "Row is out of range", row);
        return data[row];
      }

      // Get the value of the matrix at a given row/column
      // if out of range throws exception.
      float Get(uint8_t row, uint8_t col) const { return GetRow(row).Get(col); }

      // Set the value of the matrix at a given row/column
      // if out of range throws exception.
      void Set(uint8_t row, uint8_t col, float value) {
        jerobins::common::ArgumentCheck<uint8_t>(row <= 3,
                                                 "Row is out of range", row);
        data[row].Set(col, value);
      }

      Matrix4 &operator=(const Matrix4 &other) {
        this->data = other.data;
        return *this;
      }

      Matrix4 &operator=(const Matrix4 &&other) { return *this = other; }

      // Multiplication
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

      Matrix4 &operator*=(const Matrix4 &&other) {
        return this->operator*=(other);
      }

      Matrix4 operator*(const Matrix4 &other) const {
        Matrix4 result(*this);
        result *= other;
        return result;
      }

      Matrix4 operator*(const Matrix4 &&other) const { return *this * other; }

      Vec4 operator*(const Vec4 &&other) const {
        Vec4 result;
        for (uint8_t row = 0; row < 4; ++row) {
          result.Set(row, data[row].Dot(other));
        }
        return result;
      }

      Matrix4 Transpose() const {
        Matrix4 result(*this);
        _MM_TRANSPOSE4_PS(result.data[0].xmm_, result.data[1].xmm_,
                          result.data[2].xmm_, result.data[3].xmm_);
        return result;
      }

    private:
      std::array<Vec4, 4> data;
    };
  }
}

#endif