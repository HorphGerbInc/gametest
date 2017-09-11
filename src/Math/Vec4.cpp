
#include <Math/Vec4.hpp>

namespace jerobins {
  namespace math {

    Vec4::Vec4() { /* Empty */ }

    Vec4::Vec4(float x, float y, float z, float w) {
      data_[0] = x;
      data_[1] = y;
      data_[2] = z;
      data_[3] = w;
    }

    Vec4::Vec4(const Vec4 &&other) { this->xmm_ = other.xmm_; }

    Vec4::Vec4(const Vec4 &other) { this->xmm_ = other.xmm_; }

    float Vec4::Get(uint8_t pos) const {
      jerobins::common::ArgumentCheck<uint8_t>(
          pos <= 3, "Vector index is out of range", pos);
      return data_[pos];
    }

    void Vec4::Set(uint8_t pos, float value) {
      jerobins::common::ArgumentCheck<uint8_t>(
          pos <= 3, "Vector index is out of range", pos);
      data_[pos] = value;
    }
  }
}
