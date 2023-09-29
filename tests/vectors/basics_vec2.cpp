#include "tests/helpers.hpp"

using namespace btx::math;
using namespace Catch::Matchers;

TEST_CASE("Vector structure", "[vectors][vector basics][Vec2]") {
    Vec2 a; // Test the default constructor

    // Accessing by member name
    REQUIRE_THAT(a.x, WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a.y, WithinAbs(0.0f, epsilon));

    // Accessing by index
    REQUIRE_THAT(a[0], WithinAbs(0.0f, epsilon));
    REQUIRE_THAT(a[1], WithinAbs(0.0f, epsilon));

    // Modifying by member name
    a.x = 1.0f;
    a.y = 2.0f;

    REQUIRE_THAT(a.x, WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(a.y, WithinAbs(2.0f, epsilon));

    // Modifying by index
    a[0] = 3.0f;
    a[1] = 2.0f;

    REQUIRE_THAT(a[0], WithinAbs(3.0f, epsilon));
    REQUIRE_THAT(a[1], WithinAbs(2.0f, epsilon));
}

TEST_CASE("Vector equality", "[vectors][vector basics][Vec2]") {
    // Unit vectors are distinct
    REQUIRE(Vec2::unit_x != Vec2::unit_y);

    // Zero vector is itself
    REQUIRE(Vec2::zero == Vec2::zero);

    // And some random samples for good measure
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec2 const a = random_vec2();
        REQUIRE(a == a);
    }
}

TEST_CASE("Vector addition", "[vectors][vector basics][Vec2]") {
    // Start with fixed values
    Vec2 a(0.0f, 9.0f);
    Vec2 b(2.0f, -1.0f);
    Vec2 c(2.0f, 8.0f);

    // Addition is commutative
    REQUIRE(a + b == b + a);

    // Addition is commutative via assignment
    Vec2 d = a;
    Vec2 e = b;
    REQUIRE((d += b) == c);
    REQUIRE((e += a) == c);

    // Addition is associative
    Vec2 f = a + b + c;
    REQUIRE((a + b) + c == f);
    REQUIRE(a + (b + c) == f);

    // Addition is associative via assignment
    Vec2 g = a;
    Vec2 h = b;
    REQUIRE((g += b) + c == f);
    REQUIRE(a + (h += c) == f);

    // Now run the same tests with random values
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        a = random_vec2();
        b = random_vec2();
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

TEST_CASE("Vector subtraction", "[vectors][vector basics][Vec2]") {
    // Start with fixed values
    Vec2 a(0.0f, 9.0f);
    Vec2 b(2.0f, -1.0f);
    Vec2 c(-2.0f, 10.0f);
    Vec2 d = a;

    REQUIRE(a - b == c);            // Basic operation
    REQUIRE(a + (-b) == c);         // Negation operator
    REQUIRE((d -= b) == c);         // Assignment operator
    REQUIRE(a - a == Vec2::zero);   // A vector minus itself is zero

    // Now run the same tests with random values
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        a = random_vec2();
        b = random_vec2();
        c = a - b;
        d = a;

        REQUIRE(a - b == c);
        REQUIRE(a + (-b) == c);
        REQUIRE((d -= b) == c);
        REQUIRE(a - a == Vec2::zero);
    }
}

TEST_CASE("Vector length", "[vectors][vector basics][Vec2]") {
    // Test the unit and zero vectors
    REQUIRE_THAT(length(Vec2::unit_x), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec2::unit_y), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length(Vec2::zero),   WithinAbs(0.0f, epsilon));

    REQUIRE_THAT(length_squared(Vec2::unit_x), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec2::unit_y), WithinAbs(1.0f, epsilon));
    REQUIRE_THAT(length_squared(Vec2::zero),   WithinAbs(0.0f, epsilon));

    // Then three samples
    Vec2 a(6.0f, 10.0f);
    float a_length = 11.66190379f;
    float a_length_squared = 136.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));

    a = { 2.0f, 9.0f };
    a_length = 9.219544457f;
    a_length_squared = 85.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));

    a = { 10.0f, -10.0f };
    a_length = 14.142135624f;
    a_length_squared = 200.0f;
    REQUIRE_THAT(length(a),  WithinAbs(a_length, epsilon));
    REQUIRE_THAT(length_squared(a), WithinAbs(a_length_squared, epsilon));
}

TEST_CASE("Vector normalization", "[vectors][vector basics][Vec2]") {
    // The unit vectors won't change
    REQUIRE(normalize(Vec2::unit_x) == Vec2::unit_x);
    REQUIRE(normalize(Vec2::unit_y) == Vec2::unit_y);

    // But these random ones might
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec2 a = random_vec2();
        Vec2 b = normalize(a);

        REQUIRE_THAT(length(b), WithinAbs(1.0f, epsilon));
    }
}

TEST_CASE("Vector scaling", "[vectors][vector basics][Vec2]") {
    // Test the unit vectors
    REQUIRE_THAT(length( 2.0f * Vec2::unit_x), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(-2.0f * Vec2::unit_y), WithinAbs(2.0f, epsilon));

    REQUIRE_THAT(length(Vec2::unit_x *  2.0f), WithinAbs(2.0f, epsilon));
    REQUIRE_THAT(length(Vec2::unit_y * -2.0f), WithinAbs(2.0f, epsilon));

    REQUIRE_THAT(length(Vec2::unit_x /  2.0f), WithinAbs(0.5f, epsilon));
    REQUIRE_THAT(length(Vec2::unit_y / -2.0f), WithinAbs(0.5f, epsilon));

    // Then random samples
    for(uint32_t i = 0u; i < TEST_REPEATS; ++i) {
        Vec2 a = random_vec2();
        Vec2 b = random_vec2();
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