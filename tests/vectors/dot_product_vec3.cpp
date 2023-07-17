#include "tests/helpers.hpp"

using namespace btx::math;
using namespace Catch::Matchers;

TEST_CASE("Basic functionality", "[vectors][dot product][Vec3]") {
    Vec3 a(4, -2, 3);
    Vec3 b(-5, 9, -1);
    float a_dot_b = -41.0f;
    REQUIRE_THAT(dot(a, b), WithinAbs(a_dot_b, epsilon));

    a = { 1, -5, 0 };
    b = { -2, 1, -1 };
    a_dot_b = -7.0f;
    REQUIRE_THAT(dot(a, b), WithinAbs(a_dot_b, epsilon));

    a = { 4, 0, -3 };
    b = { -1, 6, -2 };
    a_dot_b = 2.0f;
    REQUIRE_THAT(dot(a, b), WithinAbs(a_dot_b, epsilon));
}

TEST_CASE("Dot product is commutative", "[vectors][dot product][Vec3]") {
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();

        REQUIRE_THAT(dot(a, b), WithinAbs(dot(b, a), epsilon));
    }
}

TEST_CASE("Dot product distributes over vector addition and subtraction",
          "[vectors][dot product][Vec3]")
{
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();
        Vec3 const c = random_vec3();

        REQUIRE_THAT(dot(a + b, c), WithinAbs(dot(c, a) + dot(c, b), epsilon));
        REQUIRE_THAT(dot(a, b + c), WithinAbs(dot(a, b) + dot(a, c), epsilon));
        REQUIRE_THAT(dot(a - b, c), WithinAbs(dot(c, a) - dot(c, b), epsilon));
        REQUIRE_THAT(dot(a, b - c), WithinAbs(dot(a, b) - dot(a, c), epsilon));
    }
}

TEST_CASE("Dot product is associative with scalar multiplication",
          "[vectors][dot product][Vec3]")
{
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();

        float const x = Catch::Generators::random(-1.0f, 1.0f).get();
        REQUIRE_THAT(x * dot(a, b), WithinAbs(dot(x * a, b), epsilon));
        REQUIRE_THAT(x * dot(a, b), WithinAbs(dot(a, x * b), epsilon));
    }
}

TEST_CASE("Dotting a vector with itself", "[vectors][dot product][Vec3]") {
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 a = random_vec3();

        // The dot product of a nonzero vector with itself must be positive
        REQUIRE(dot(a, a) > 0.0f);

        // It should also be the vector's length squared
        REQUIRE_THAT(dot(a, a), WithinAbs(length_squared(a), epsilon));

        // Normalized vectors dotted with themselves always yield 1
        a = normalize(a);
        REQUIRE_THAT(dot(a, a), WithinAbs(1.0f, epsilon));
    }

    // But dotting the zero vector with itself will yield zero
    REQUIRE_THAT(dot(Vec3::zero, Vec3::zero), WithinAbs(0.0f, epsilon));
}

TEST_CASE("Dotting a vector with its inverse", "[vectors][dot product][Vec3]") {
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 a = random_vec3();

        // Dotting a vector with its inverse will yield the length squared, but
        // negative
        REQUIRE_THAT(dot(a, -a), WithinAbs(-length_squared(a), epsilon));

        // Likewise, a normalized vector dotted with its inverse yields -1
        a = normalize(a);
        REQUIRE_THAT(dot(a, -a), WithinAbs(-1.0f, epsilon));
    }
}

TEST_CASE("Unit vectors are perpendicular", "[vectors][dot product][Vec3]") {
    REQUIRE_THAT(dot(Vec3::unit_x, Vec3::unit_y), WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(dot(Vec3::unit_x, Vec3::unit_z), WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(dot(Vec3::unit_y, Vec3::unit_z), WithinAbs(0.0f, epsilon));
}