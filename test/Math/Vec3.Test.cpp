

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

TEST_CASE("[Vec3] : Assignment works") {
    jerobins::math::Vec3<> vec1(0,2,3);
    REQUIRE(vec1.X() == 0);
    REQUIRE(vec1.Y() == 2);
    REQUIRE(vec1.Z() == 3);

    jerobins::math::Vec3<> vec2(1,3,4);
    REQUIRE(vec2.X() == 1);
    REQUIRE(vec2.Y() == 3);
    REQUIRE(vec2.Z() == 4);
    
    vec2 = vec1;
    REQUIRE(vec2.X() == 0);
    REQUIRE(vec2.Y() == 2);
    REQUIRE(vec2.Z() == 3);
}