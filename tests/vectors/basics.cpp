#include "tests/helpers.hpp"

using namespace btx::math;
using namespace Catch::Matchers;

TEST_CASE("Vector structure", "[vectors][vector basics]") {
    Vec3 a(1, 2, 3);
    // accessing by member name
    REQUIRE_THAT(a.x, WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(a.y, WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(a.z, WithinAbs(3.0f, epsilon));

    // accessing by index
    REQUIRE_THAT(a[0], WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(a[1], WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(a[2], WithinAbs(3.0f, epsilon));

    // modifying by member name
    a.x *= 2.0f;
    REQUIRE_THAT(a.x, WithinAbs(2.0f, epsilon));
    REQUIRE(a == Vec3{ 2, 2, 3 });

    // modifying by index
    a[1] /= 2.0f;
    REQUIRE_THAT(a[1], WithinAbs(1.0f, epsilon));
    REQUIRE(a == Vec3{ 2, 1, 3 });
}

TEST_CASE("Vector addition", "[vectors][vector basics]") {
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec3 const a = random_vec3();
        Vec3 const b = random_vec3();

        // Addition is commutative
        REQUIRE(a + b == b + a);

        // Addition is commutative via assignment
        Vec3 const c = a + b;
        Vec3 d = a;
        Vec3 e = b;
        REQUIRE((d += b) == c);
        REQUIRE((e += a) == c);

        // Addition is associative
        Vec3 const f = a + b + c;
        REQUIRE((a + b) + c == f);
        REQUIRE(a + (b + c) == f);

        // Addition is associative via assignment
        Vec3 g = a;
        Vec3 h = b;
        REQUIRE((g += b) + c == f);
        REQUIRE(a + (h += c) == f);
    }
}

TEST_CASE("Vector subtraction", "[vectors][vector basics]") {
    Vec3 const a(0, 9, -3);
    Vec3 const b(2, -1, 6);
    Vec3 const c(-2, 10, -9);
    Vec3 d = a;

    REQUIRE(a - b == c);            // Basic operation
    REQUIRE(a + (-b) == c);         // Negation operator
    REQUIRE((d -= b) == c);         // Assignment operator
    REQUIRE(a - a == Vec3::zero);   // A vector minus itself is zero
}

TEST_CASE("Vector length", "[vectors][vector basics]") {
    // Test the unit and zero vectors
    REQUIRE_THAT(length(Vec3::unit_x), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec3::unit_y), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec3::unit_z), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec3::zero),   WithinAbs(0.0f, epsilon));

    REQUIRE_THAT(length_squared(Vec3::unit_x), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec3::unit_y), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec3::unit_z), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec3::zero),   WithinAbs(0.0f, epsilon));

    // Then three samples
    Vec3 a(6, 10, 1);
    float a_length = 11.70469991f;
    float a_length_squared = 137.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));

    a = { 2, 9, 8 };
    a_length = 12.20655562f;
    a_length_squared = 149.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));

    a = { 10, -10, 5 };
    a_length = 15.0f;
    a_length_squared = 225.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));
}

TEST_CASE("Vector normalization", "[vectors][vector basics]") {
    // The unit vectors won't change
    REQUIRE(normalize(Vec3::unit_x) == Vec3::unit_x);
    REQUIRE(normalize(Vec3::unit_y) == Vec3::unit_y);
    REQUIRE(normalize(Vec3::unit_z) == Vec3::unit_z);

    // But these three will
    Vec3 a(-4, -3, -5);
    float a_length = 7.071067812f;
    Vec3 b(-0.5656854249f, -0.4242640687f, -0.7071067812f);
    REQUIRE_THAT(length(a), WithinAbs(a_length, epsilon));
    REQUIRE(normalize(a) == b);
    REQUIRE_THAT(length(normalize(a)), WithinAbs(1.0f, epsilon));

    a = { -1, 1, 1 };
    a_length = 1.732050808f;
    b = { -0.5773502692f, 0.5773502692f, 0.5773502692f };
    REQUIRE_THAT(length(a), WithinAbs(a_length, epsilon));
    REQUIRE(normalize(a) == b);
    REQUIRE_THAT(length(normalize(a)), WithinAbs(1.0f, epsilon));

    a = { 0, -4, 5 };
    a_length = 6.403124237f;
    b = { 0.0f, -0.6246950476f, 0.7808688094f };
    REQUIRE_THAT(length(a), WithinAbs(a_length, epsilon));
    REQUIRE(normalize(a) == b);
    REQUIRE_THAT(length(normalize(a)), WithinAbs(1.0f, epsilon));
}

TEST_CASE("Vector scaling", "[vectors][vector basics]") {
    // Test the unit vectors
    REQUIRE_THAT(length( 2.0f * Vec3::unit_x), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(-2.0f * Vec3::unit_y), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length( 0.5f * Vec3::unit_z), WithinAbs(0.5f, epsilon));

    REQUIRE_THAT(length(Vec3::unit_x *  2.0f), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(Vec3::unit_y * -2.0f), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(Vec3::unit_z *  0.5f), WithinAbs(0.5f, epsilon));

    REQUIRE_THAT(length(Vec3::unit_x /  2.0f), WithinAbs(0.5f, epsilon));
    REQUIRE_THAT(length(Vec3::unit_y / -2.0f), WithinAbs(0.5f, epsilon));
    REQUIRE_THAT(length(Vec3::unit_z /  0.5f), WithinAbs(2.0f, epsilon));

    // Then three samples
    Vec3 a(6, 10, 1);
    Vec3 b(0, -1, 4);
    float a_length = 11.70469991f;
    REQUIRE_THAT(length(2.0f * a), WithinAbs(2.0f * a_length,  epsilon));
    // Scalars via assignment operator
    REQUIRE_THAT(length(a *= -2.0f), WithinAbs(2.0f * a_length, epsilon));
    REQUIRE_THAT(length(a /= 2.0f), WithinAbs(a_length, epsilon));
    // Scalar multiplication distributes over addition
    REQUIRE(-1.5f * (a + b) == (-1.5f * a) + (-1.5f * b));

    a = { 2, 9, 8 };
    b = { -3, 1, 0 };
    a_length = 12.20655562f;
    REQUIRE_THAT(length(2.0f * a), WithinAbs(2.0f * a_length,  epsilon));
    // Scalars via assignment operator
    REQUIRE_THAT(length(a *= -2.0f), WithinAbs(2.0f * a_length, epsilon));
    REQUIRE_THAT(length(a /= 2.0f), WithinAbs(a_length, epsilon));
    // Scalar multiplication distributes over addition
    REQUIRE(-1.5f * (a + b) == (-1.5f * a) + (-1.5f * b));

    a = { 10, -10, 5 };
    b = { 2, -5, 3 };
    a_length = 15.0f;
    REQUIRE_THAT(length(2.0f * a), WithinAbs(2.0f * a_length,  epsilon));
    // Scalars via assignment operator
    REQUIRE_THAT(length(a *= -2.0f), WithinAbs(2.0f * a_length, epsilon));
    REQUIRE_THAT(length(a /= 2.0f), WithinAbs(a_length, epsilon));
    // Scalar multiplication distributes over addition
    REQUIRE(-1.5f * (a + b) == (-1.5f * a) + (-1.5f * b));
}