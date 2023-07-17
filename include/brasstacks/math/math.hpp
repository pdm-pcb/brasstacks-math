#ifndef BRASSTACKS_MATH_MATH_HPP
#define BRASSTACKS_MATH_MATH_HPP

#include "brasstacks/math/pch.hpp"
#include "brasstacks/math/Vec2.hpp"
#include "brasstacks/math/Vec3.hpp"
#include "brasstacks/math/Vec4.hpp"

namespace btx::math {

// Insist on keeping the data simple
static_assert(sizeof(Vec2) == sizeof(float) * 2);
static_assert(sizeof(Vec3) == sizeof(float) * 3);
static_assert(sizeof(Vec4) == sizeof(float) * 4);

static_assert(std::is_trivially_copyable_v<Vec2>);
static_assert(std::is_trivially_copyable_v<Vec3>);
static_assert(std::is_trivially_copyable_v<Vec4>);

static_assert(std::is_trivially_copy_constructible_v<Vec2>);
static_assert(std::is_trivially_copy_constructible_v<Vec3>);
static_assert(std::is_trivially_copy_constructible_v<Vec4>);

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
[[nodiscard]] float length_squared(Vec2 const &v);
[[nodiscard]] float length(Vec2 const &v);

[[nodiscard]] float length_squared(Vec3 const &v);
[[nodiscard]] float length(Vec3 const &v);

[[nodiscard]] float length_squared(Vec4 const &v);
[[nodiscard]] float length(Vec4 const &v);

[[nodiscard]] Vec2 normalize(Vec2 const &v);
[[nodiscard]] Vec3 normalize(Vec3 const &v);
[[nodiscard]] Vec4 normalize(Vec4 const &v);

[[nodiscard]] float dot(Vec2 const &a, Vec2 const &b);
[[nodiscard]] float dot(Vec3 const &a, Vec3 const &b);
[[nodiscard]] float dot(Vec4 const &a, Vec4 const &b);

[[nodiscard]] Vec3 cross(Vec3 const &a, Vec3 const &b);

} // namespace btx::math

#endif // BRASSTACKS_MATH_MATH_HPP