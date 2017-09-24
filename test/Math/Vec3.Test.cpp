

#include <catch.hpp>

#include <Math/Vec3.hpp>

TEST_CASE("[Vec3]: Create an empty vector") {
    jerobins::math::Vec3<> vec;
    REQUIRE(vec.X() == 0);
    REQUIRE(vec.Y() == 0);
    REQUIRE(vec.Z() == 0);
    REQUIRE(vec.Get(0) == vec.X());
    REQUIRE(vec.Get(1) == vec.Y());
    REQUIRE(vec.Get(1) == vec.Z());
    
    vec.Set(0, 1.0);
    REQUIRE(vec.X() == 1.0);
    REQUIRE(vec.Get(0) == vec.X());

    vec.Set(1, 1.3f);
    REQUIRE(vec.Y() == 1.3f);
    REQUIRE(vec.Get(1) == vec.Y());
}

TEST_CASE("[Vec3] : Cross Product") {
    jerobins::math::Vec3<> vec;
    REQUIRE(vec.X() == 0);
    REQUIRE(vec.Y() == 0);
    REQUIRE(vec.Z() == 0);
    REQUIRE(vec.Get(0) == vec.X());
    REQUIRE(vec.Get(1) == vec.Y());
    REQUIRE(vec.Get(1) == vec.Z());
    
    vec.Set(0, 1.0);
    REQUIRE(vec.X() == 1.0);
    REQUIRE(vec.Get(0) == vec.X());

    vec.Set(1, 1.3f);
    REQUIRE(vec.Y() == 1.3f);
    REQUIRE(vec.Get(1) == vec.Y());
}