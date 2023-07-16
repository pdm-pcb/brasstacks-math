#ifndef BRASSTACKS_MATH_TESTS_HELPERS_HPP
#define BRASSTACKS_MATH_TESTS_HELPERS_HPP

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/generators/catch_generators_random.hpp>

#include "brasstacks/math/math.hpp"

static uint32_t constexpr TEST_REPEATS = 3u;

inline auto random_vec3(float const min = -1.0f, float const max = 1.0f) {
    return btx::math::Vec3(
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get(),
        Catch::Generators::random(min, max).get()
    );
}

#endif // BRASSTACKS_MATH_TESTS_HELPERS_HPP