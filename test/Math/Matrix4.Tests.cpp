
#include <catch.hpp>

#include <Math/Matrix4.hpp>

TEST_CASE("Matrix4", "CreateZeroMatrix")
{
    jerobins::math::Matrix4 ret;
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            REQUIRE(0 == ret.Get(row, col));
        }
    }
}
