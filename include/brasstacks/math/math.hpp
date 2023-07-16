#ifndef BRASSTACKS_MATH_MATH_HPP
#define BRASSTACKS_MATH_MATH_HPP

#include "brasstacks/math/pch.hpp"
#include "brasstacks/math/Vec3.hpp"

namespace btx::math {

// Insist on keeping the data simple
static_assert(sizeof(Vec3) == sizeof(float) * 3);
static_assert(std::is_trivially_copyable_v<Vec3>);
static_assert(std::is_trivially_copy_constructible_v<Vec3>);

// For pretty-printing
static uint8_t constexpr print_precs = 8u;
static uint8_t constexpr print_width = 2u * print_precs + 2u;

// General constants
static float constexpr epsilon = 1.0e-4;
static float constexpr pi = std::numbers::pi_v<float>;
static float constexpr pi_over_one_eighty = pi / 180.0f;
static float constexpr one_eighty_over_pi = 180.0f / pi;

// Conversions
[[nodiscard]] inline float radians(float const deg) {
    return deg * pi_over_one_eighty;
}
[[nodiscard]] inline float degrees(float const rad) {
    return rad * one_eighty_over_pi;
}

// =============================================================================
// Vector operations
[[nodiscard]] inline float length_squared(Vec3 const &v) {
    return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

[[nodiscard]] inline float length(Vec3 const &v) {
    float length_sq = length_squared(v);

    // If we're dealing with the zero vector, return zero
    if(std::abs(length_sq) < epsilon) {
        return 0.0f;
    }

    // If it's a unit vector, skip the square root calculation
    if(std::abs(length_sq - 1.0f) < epsilon) {
        return length_sq;
    }

    return std::sqrt(length_sq);
}

[[nodiscard]] Vec3 normalize(Vec3 const &v);

[[nodiscard]] float dot(Vec3 const &a, Vec3 const &b);
[[nodiscard]] Vec3 cross(Vec3 const &a, Vec3 const &b);

} // namespace btx::math

#endif // BRASSTACKS_MATH_MATH_HPP