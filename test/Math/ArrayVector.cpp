
#include <catch.hpp>

#include <Math/ArrayVector.hpp>

const float x = 1.0;
const float y = 1.0;

class Vec: public jerobins::math::ArrayVector<Vec,2> {

};

TEST_CASE("[ArrayVector] : Create empty ArrayVector") {
    Vec vec;
    REQUIRE(vec.Get(0) == 0);
    REQUIRE(vec.Get(1) == 0);

    vec.Set(0, x);
    REQUIRE(vec.Get(0) == x);

    vec.Set(1, y);
    REQUIRE(vec.Get(1) == y);
}
