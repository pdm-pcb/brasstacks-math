#include "tests/helpers.hpp"

using namespace btx::math;
using namespace Catch::Matchers;

TEST_CASE("Basic functionality", "[vectors][cross product]") {
    Vec3 a(-2, 10, -6);
    Vec3 b(8, -1, 2);
    Vec3 a_cross_b(14, -44, -78);

    REQUIRE(cross(a, b) == a_cross_b);

    a = { 7, 1, 0 };
    b = { 4, 8, -10 };
    a_cross_b = { -10, 70, 52 };

    REQUIRE(cross(a, b) == a_cross_b);

    a = { 1, 8, 5 };
    b = { 3, -7, 0 };
    a_cross_b = { 35, 15, -31 };

    REQUIRE(cross(a, b) == a_cross_b);
}

TEST_CASE("Cross product is anti-commutative", "[vectors][cross product]") {
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();
        Vec3 const a_cross_b = cross(a, b);

        REQUIRE(a_cross_b == -cross(b, a));
    }
}

TEST_CASE("Crossing negative vectors yields the same result",
          "[vectors][cross product]")
{
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();
        Vec3 const a_cross_b = cross(a, b);

        REQUIRE(a_cross_b == cross(-a, -b));
    }
}

TEST_CASE("Crossing a vector with itself yields the zero vector",
          "[vectors][cross product]")
{
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();

        REQUIRE(cross(a, a) == Vec3::zero);
    }
}

TEST_CASE("Cross product distributes over vector addition and subtraction",
          "[vectors][cross product]")
{
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();
        Vec3 const c = random_vec3();

        REQUIRE(cross(a + b, c) == cross(a, c) + cross(b, c));
        REQUIRE(cross(a, b + c) == cross(a, b) + cross(a, c));
        REQUIRE(cross(a - b, c) == cross(a, c) - cross(b, c));
        REQUIRE(cross(a, b - c) == cross(a, b) - cross(a, c));
    }
}

TEST_CASE("Cross product is associative with scalar multiplication",
          "[vectors][cross product]")
{
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();

        float const x = Catch::Generators::random(-1.0f, 1.0f).get();
        REQUIRE(x * cross(a, b) == cross(x * a, b));
        REQUIRE(x * cross(a, b) == cross(a, x * b));
    }
}

TEST_CASE("Crossing parallel vectors yields zero", "[vectors][cross product]") {
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 a = random_vec3();

        // Crossing a vector with itself or its inverse yields the zero vector
        REQUIRE(cross(a, a) == Vec3::zero);
        REQUIRE(cross(a, -a) == Vec3::zero);
        REQUIRE(cross(-a, a) == Vec3::zero);

        // Crossing anything with the zero vector also yields the zero vector
        REQUIRE(cross(a, Vec3::zero) == Vec3::zero);
        REQUIRE(cross(Vec3::zero, a) == Vec3::zero);
    }
}

TEST_CASE("Crossing unit vectors produces the a third unit vector",
          "[vectors][cross product]")
{
    REQUIRE(cross(Vec3::unit_x, Vec3::unit_y) == Vec3::unit_z);
    REQUIRE(cross(Vec3::unit_z, Vec3::unit_x) == Vec3::unit_y);
    REQUIRE(cross(Vec3::unit_y, Vec3::unit_z) == Vec3::unit_x);
}