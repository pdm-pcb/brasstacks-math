#ifndef BRASSTACKS_MATH_TESTS_HELPERS_HPP
#define BRASSTACKS_MATH_TESTS_HELPERS_HPP

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/generators/catch_generators_random.hpp>

#include "brasstacks/math/math.hpp"

static uint32_t constexpr TEST_REPEATS = 10u;

inline auto random_vec2(float const min = -10.0f, float const max = 10.0f) {
    return btx::math::Vec2(
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get()
    );
}

inline auto random_vec3(float const min = -10.0f, float const max = 10.0f) {
    return btx::math::Vec3(
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get()
    );
}

inline auto random_vec4(float const min = -10.0f, float const max = 10.0f) {
    return btx::math::Vec4(
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get()
    );
}

#endif // BRASSTACKS_MATH_TESTS_HELPERS_HPP