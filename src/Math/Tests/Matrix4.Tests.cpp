
#include "Math/Matrix4.hpp"
#include "gtest/gtest.h"
namespace
{
TEST(Matrix4, CreateZeroMatrix)
{
    jerobins::math::Matrix4 ret;
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            ASSERT_EQ(0, ret.Get(row, col));
        }
    }
}
}