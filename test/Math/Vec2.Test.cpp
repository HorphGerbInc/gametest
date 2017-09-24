

#include <catch.hpp>

#include <Math/Vec2.hpp>
#include <Math/SIMD/Vec2.hpp>

TEST_CASE("[Vec2] : Create empty vector") {
    jerobins::math::Vec2 vec;
    jerobins::math::simd::Vec2 simdVec;
    REQUIRE(vec.X() == 0);
    REQUIRE(vec.Y() == 0);
    REQUIRE(vec.Get(0) == vec.X());
    REQUIRE(vec.Get(1) == vec.Y());

    vec.Set(0, 1.0);
    REQUIRE(vec.X() == 1.0);
    REQUIRE(vec.Get(0) == vec.X());

    vec.Set(1, 1.3f);
    REQUIRE(vec.Y() == 1.3f);
    REQUIRE(vec.Get(1) == vec.Y());
}

TEST_CASE("[Vec2] : Can assign") {
    float x = 1.0;
    float y = 2.0;

    jerobins::math::Vec2 from(x , y);
    jerobins::math::Vec2 to;

    to = from;
    REQUIRE(from.X() == x);
    REQUIRE(from.Y() == y);

    REQUIRE(from.X() == to.X());
    REQUIRE(from.Y() == to.Y());
}

TEST_CASE("[Vec2] : Copy constructor") {
    float x = 1.0;
    float y = 2.0;

    jerobins::math::Vec2 from(x , y);
    jerobins::math::Vec2 to(from);

    REQUIRE(from.X() == to.X());
    REQUIRE(from.Y() == to.Y());

    to = from;
    REQUIRE(from.X() == x);
    REQUIRE(from.Y() == y);

    REQUIRE(from.X() == to.X());
    REQUIRE(from.Y() == to.Y());

}