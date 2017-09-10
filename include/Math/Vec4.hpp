
#ifndef _VEC4_HPP_
#define _VEC4_HPP_

#include <intrin.h>

#include <Common/ArgumentCheck.hpp>
#include <Math/VectorBase.hpp>

namespace jerobins
{
namespace math
{

class Vec4 : public VectorBase<Vec4>
{
  public:
    Vec4();
    Vec4(float x, float y, float z, float w);
    Vec4(const Vec4 &&other);
    Vec4(const Vec4 &other);

    float Get(uint8_t pos) const;
    void Set(uint8_t pos, float value);

    friend class Matrix4;
};
}
}

#endif