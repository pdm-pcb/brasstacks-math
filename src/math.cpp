#include "brasstacks/math/math.hpp"

namespace btx::math {

// "Namespace-global" statics
Vec3 const Vec3::zero   { 0.0f, 0.0f, 0.0f };
Vec3 const Vec3::unit_x { 1.0f, 0.0f, 0.0f };
Vec3 const Vec3::unit_y { 0.0f, 1.0f, 0.0f };
Vec3 const Vec3::unit_z { 0.0f, 0.0f, 1.0f };

// =============================================================================
// Vector operations
Vec3 normalize(Vec3 const &v) {
    Vec3 result = v;

    auto const length = length_squared(v);

    // If we're working with the zero vector or a vector that's already
    // normalized, just return
    if(length < epsilon || std::abs(length - 1.0f) < epsilon) {
        return result;
    }

    float const length_recip = 1.0f / std::sqrt(length);

    result.x *= length_recip;
    result.y *= length_recip;
    result.z *= length_recip;

    return result;
}

float dot(Vec3 const &a, Vec3 const &b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 cross(Vec3 const &a, Vec3 const &b) {
    return Vec3 {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x),
    };
}

} // namespace btx::math