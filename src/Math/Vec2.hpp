
#ifndef _VEC3_HPP_
#define _VEC3_HPP_

#include <Math/VectorBase.hpp>

namespace jerobins
{
namespace math
{

class Vec2 : public VectorBase<Vec2>
{
  public:
    Vec2(float x, float y)
    {
        data_[0] = x;
        data_[1] = y;
    }

    Vec2(const float *data)
    {
        data_[0] = data[0];
        data_[1] = data[1];
    }

    Vec2(const Vec2 &&rhs) : xmm_(rhs.xmm_)
    {
        /* Empty */
    }
};
}
}

#endif