

#include <catch.hpp>

#include <Math/Vec4.hpp>
#include <Math/SIMD/Vec4.hpp>
#include <Common/Timer.hpp>

const float x = 1.2f;
const float y = 1.2f;
const float z = 1.2f;
const float w = 1.2f;
const float values[4] = {x, y, z, w};
const float scale = 1252.5;

TEST_CASE("[Vec4] : Create empty vector") {
  jerobins::math::Vec4<> vec;
  REQUIRE(vec.X() == 0);
  REQUIRE(vec.Y() == 0);
  REQUIRE(vec.Z() == 0);
  REQUIRE(vec.W() == 0);
  REQUIRE(vec.Get(0) == vec.X());
  REQUIRE(vec.Get(1) == vec.Y());
  REQUIRE(vec.Get(2) == vec.Z());
  REQUIRE(vec.Get(3) == vec.W());
}

TEST_CASE("[Vec4] : Set and Get works") {
  jerobins::math::Vec4<> vec;
  vec.SetX(x);
  REQUIRE(vec.X() == x);
  vec.SetY(y);
  REQUIRE(vec.Y() == y);
}

TEST_CASE("[Vec4] : Can assign") {

  jerobins::math::Vec4<> from(x, y, z, w);
  jerobins::math::Vec4<> to;

  to = from;
  REQUIRE(from.X() == x);
  REQUIRE(from.Y() == y);

  REQUIRE(from.X() == to.X());
  REQUIRE(from.Y() == to.Y());
}

TEST_CASE("[Vec4] : Copy constructor") {

  jerobins::math::Vec4<> from(x, y, z, w);
  jerobins::math::Vec4<> to(from);

  REQUIRE(from.X() == to.X());
  REQUIRE(from.Y() == to.Y());

  to = from;
  REQUIRE(from.X() == x);
  REQUIRE(from.Y() == y);
  REQUIRE(from.Z() == z);
  REQUIRE(from.W() == w);

  REQUIRE(from.X() == to.X());
  REQUIRE(from.Y() == to.Y());
  REQUIRE(from.Z() == to.Z());
  REQUIRE(from.W() == to.W());
}

TEST_CASE("[vec4] : Scalar multiple") {

  jerobins::math::Vec4<> vec(x, y, z, w);
  vec *= scale;
  REQUIRE(vec.X() == x * scale);
  REQUIRE(vec.Y() == y * scale);
  REQUIRE(vec.Z() == z * scale);
  REQUIRE(vec.W() == w * scale);
}

TEST_CASE("[vec4] : Vector addition") {

  jerobins::math::Vec4<> vec1(x, y, z, w);
  jerobins::math::Vec4<> vec2(x * scale, y * scale, z * scale, w * scale);
  jerobins::math::Vec4<> vec3 = vec1 + vec2;

  for (int i = 0; i < 4; ++i) {
    REQUIRE(vec1.Get(i) == values[i]);
    REQUIRE(vec2.Get(i) == scale * values[i]);
    REQUIRE(vec3.Get(i) == (vec1.Get(i) + vec2.Get(i)));
  }
}

TEST_CASE("[vec4] : Vector subtraction") {

  jerobins::math::Vec4<> vec1(x, y, z, w);
  jerobins::math::Vec4<> vec2(x * scale, y * scale, z * scale, w * scale);
  jerobins::math::Vec4<> vec3 = vec1 - vec2;

  for (int i = 0; i < 4; ++i) {
    REQUIRE(vec1.Get(i) == values[i]);
    REQUIRE(vec2.Get(i) == scale * values[i]);
    REQUIRE(vec3.Get(i) == (vec1.Get(i) - vec2.Get(i)));
  }
}

TEST_CASE("[vec4] : Dot product") {

	jerobins::math::Vec4<> vec1(x, y, z, w);
	jerobins::math::Vec4<> vec2(x * scale, y * scale, z * scale, w * scale);
	float dot = vec1.Dot(vec2);
	float answer = 0;
	for (int i = 0; i < 4; ++i)
		answer += vec1.Get(i) * vec2.Get(i);
	REQUIRE(dot == answer);
}

TEST_CASE("[vec4] : Dot product performance") {

	jerobins::math::Vec4<> vec1(x, y, z, w);
	jerobins::math::Vec4<> vec2(x * scale, y * scale, z * scale, w * scale);
	for (int i = 0; i < 1000000; ++i) {
		float dot = vec1.Dot(vec2);
	}
}

TEST_CASE("[simd][vec4] : Dot product performance") {

	jerobins::math::simd::Vec4 vec1(x, y, z, w);
	jerobins::math::simd::Vec4 vec2(x * scale, y * scale, z * scale, w * scale);
	for (int i = 0; i < 1000000; ++i) {
		float dot = vec1.Dot(vec2);
	}
}