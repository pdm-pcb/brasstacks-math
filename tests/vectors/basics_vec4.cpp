#include "tests/helpers.hpp"

using namespace btx::math;
using namespace Catch::Matchers;

TEST_CASE("Vector structure", "[vectors][vector basics][Vec4]") {
    Vec4 a; // Test the default constructor

    // Accessing by member name
    REQUIRE_THAT(a.x, WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a.y, WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a.z, WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a.w, WithinAbs(0.0f, epsilon));

    // Accessing by index
    REQUIRE_THAT(a[0], WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a[1], WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a[2], WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a[3], WithinAbs(0.0f, epsilon));

    // Modifying by member name
    a.x = 1.0f;
    a.y = 2.0f;
    a.z = 3.0f;
    a.w = 4.0f;

    REQUIRE_THAT(a.x, WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(a.y, WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(a.z, WithinAbs(3.0f, epsilon));
    REQUIRE_THAT(a.w, WithinAbs(4.0f, epsilon));

    // Modifying by index
    a[0] = 4.0f;
    a[1] = 3.0f;
    a[2] = 2.0f;
    a[3] = 1.0f;

    REQUIRE_THAT(a[0], WithinAbs(4.0f, epsilon));
    REQUIRE_THAT(a[1], WithinAbs(3.0f, epsilon));
    REQUIRE_THAT(a[2], WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(a[3], WithinAbs(1.0f, epsilon));
}

TEST_CASE("Vector equality", "[vectors][vector basics][Vec4]") {
    // Unit vectors are distinct
    REQUIRE(Vec4::unit_x != Vec4::unit_y);
    REQUIRE(Vec4::unit_x != Vec4::unit_z);
    REQUIRE(Vec4::unit_x != Vec4::unit_w);
    REQUIRE(Vec4::unit_y != Vec4::unit_z);
    REQUIRE(Vec4::unit_y != Vec4::unit_w);
    REQUIRE(Vec4::unit_z != Vec4::unit_w);

    // Zero vector is itself
    REQUIRE(Vec4::zero == Vec4::zero);

    // And some random samples for good measure
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec4 const a = random_vec4();
        REQUIRE(a == a);
    }
}

TEST_CASE("Vector addition", "[vectors][vector basics][Vec4]") {
    // Start with fixed values
    Vec4 a(0.0f, 9.0f, -3.0f, 2.0f);
    Vec4 b(2.0f, -1.0f, 6.0f, 5.0f);
    Vec4 c(2.0f, 8.0f, 3.0f, 7.0f);

    // Addition is commutative
    REQUIRE(a + b == b + a);

    // Addition is commutative via assignment
    Vec4 d = a;
    Vec4 e = b;
    REQUIRE((d += b) == c);
    REQUIRE((e += a) == c);

    // Addition is associative
    Vec4 f = a + b + c;
    REQUIRE((a + b) + c == f);
    REQUIRE(a + (b + c) == f);

    // Addition is associative via assignment
    Vec4 g = a;
    Vec4 h = b;
    REQUIRE((g += b) + c == f);
    REQUIRE(a + (h += c) == f);

    // Now run the same tests with random values
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        a = random_vec4();
        b = random_vec4();
        c = a + b;

        REQUIRE(a + b == b + a);

        d = a;
        e = b;
        REQUIRE((d += b) == c);
        REQUIRE((e += a) == c);

        f = a + b + c;
        REQUIRE((a + b) + c == f);
        REQUIRE(a + (b + c) == f);

        g = a;
        h = b;
        REQUIRE((g += b) + c == f);
        REQUIRE(a + (h += c) == f);
    }
}

TEST_CASE("Vector subtraction", "[vectors][vector basics][Vec4]") {
    // Start with fixed values
    Vec4 a(0.0f, 9.0f, -3.0f, 2.0f);
    Vec4 b(2.0f, -1.0f, 6.0f, 5.0f);
    Vec4 c(-2.0f, 10.0f, -9.0f, -3.0f);
    Vec4 d = a;

    REQUIRE(a - b == c);            // Basic operation
    REQUIRE(a + (-b) == c);         // Negation operator
    REQUIRE((d -= b) == c);         // Assignment operator
    REQUIRE(a - a == Vec4::zero);   // A vector minus itself is zero

    // Now run the same tests with random values
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        a = random_vec4();
        b = random_vec4();
        c = a - b;
        d = a;

        REQUIRE(a - b == c);
        REQUIRE(a + (-b) == c);
        REQUIRE((d -= b) == c);
        REQUIRE(a - a == Vec4::zero);
    }
}

TEST_CASE("Vector length", "[vectors][vector basics][Vec4]") {
    // Test the unit and zero vectors
    REQUIRE_THAT(length(Vec4::unit_x), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec4::unit_y), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec4::unit_z), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec4::zero),   WithinAbs(0.0f, epsilon));

    REQUIRE_THAT(length_squared(Vec4::unit_x), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec4::unit_y), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec4::unit_z), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec4::zero),   WithinAbs(0.0f, epsilon));

    // Then three samples
    Vec4 a(6.0f, 10.0f, 1.0f, -2.0f);
    float a_length = 11.874342087f;
    float a_length_squared = 141.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));

    a = { 2.0f, 9.0f, 8.0f, 0.0f };
    a_length = 12.20655562f;
    a_length_squared = 149.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));

    a = { 10.0f, -10.0f, 5.0f, 1.0f };
    a_length = 15.033296378f;
    a_length_squared = 226.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));
}

TEST_CASE("Vector normalization", "[vectors][vector basics][Vec4]") {
    // The unit vectors won't change
    REQUIRE(normalize(Vec4::unit_x) == Vec4::unit_x);
    REQUIRE(normalize(Vec4::unit_y) == Vec4::unit_y);
    REQUIRE(normalize(Vec4::unit_z) == Vec4::unit_z);
    REQUIRE(normalize(Vec4::unit_w) == Vec4::unit_w);

    // But these random ones might
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec4 a = random_vec4();
        Vec4 b = normalize(a);

        REQUIRE_THAT(length(b), WithinAbs(1.0f, epsilon));
    }
}

TEST_CASE("Vector scaling", "[vectors][vector basics][Vec4]") {
    // Test the unit vectors
    REQUIRE_THAT(length( 2.0f * Vec4::unit_x), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(-2.0f * Vec4::unit_y), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length( 0.5f * Vec4::unit_z), WithinAbs(0.5f, epsilon));

    REQUIRE_THAT(length(Vec4::unit_x *  2.0f), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(Vec4::unit_y * -2.0f), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(Vec4::unit_z *  0.5f), WithinAbs(0.5f, epsilon));

    REQUIRE_THAT(length(Vec4::unit_x /  2.0f), WithinAbs(0.5f, epsilon));
    REQUIRE_THAT(length(Vec4::unit_y / -2.0f), WithinAbs(0.5f, epsilon));
    REQUIRE_THAT(length(Vec4::unit_z /  0.5f), WithinAbs(2.0f, epsilon));

    // Then random samples
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec4 a = random_vec4();
        Vec4 b = random_vec4();
        float const a_length = length(a);

        // operator*() overloads
        REQUIRE_THAT(length(2.0f * a), WithinAbs(2.0f * a_length,  epsilon));
        REQUIRE_THAT(length(a * 3.0f), WithinAbs(3.0f * a_length,  epsilon));

        // operator/()
        REQUIRE_THAT(length(a / 4.0f), WithinAbs(a_length / 4.0f,  epsilon));

        // Scalars via assignment operators
        REQUIRE_THAT(length(a *= -5.0f), WithinAbs(5.0f * a_length, epsilon));
        REQUIRE_THAT(length(a /= 5.0f), WithinAbs(a_length, epsilon));

        // Scalar multiplication distributes over addition
        REQUIRE(-1.5f * (a + b) == (-1.5f * a) + (-1.5f * b));
    }
}