#include "brasstacks/math/math.hpp"

namespace btx::math {

// "Namespace-global" statics
Vec2 const Vec2::zero   { 0.0f, 0.0f };
Vec2 const Vec2::unit_x { 1.0f, 0.0f };
Vec2 const Vec2::unit_y { 0.0f, 1.0f };

Vec3 const Vec3::zero   { 0.0f, 0.0f, 0.0f };
Vec3 const Vec3::unit_x { 1.0f, 0.0f, 0.0f };
Vec3 const Vec3::unit_y { 0.0f, 1.0f, 0.0f };
Vec3 const Vec3::unit_z { 0.0f, 0.0f, 1.0f };

Vec4 const Vec4::zero   { 0.0f, 0.0f, 0.0f, 0.0f };
Vec4 const Vec4::unit_x { 1.0f, 0.0f, 0.0f, 0.0f };
Vec4 const Vec4::unit_y { 0.0f, 1.0f, 0.0f, 0.0f };
Vec4 const Vec4::unit_z { 0.0f, 0.0f, 1.0f, 0.0f };
Vec4 const Vec4::unit_w { 0.0f, 0.0f, 0.0f, 1.0f };

// =============================================================================
// Vec2 length
float length_squared(Vec2 const &v) {
    return (v.x * v.x) + (v.y * v.y);
}

float length(Vec2 const &v) {
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

// =============================================================================
// Vec3 length
float length_squared(Vec3 const &v) {
    return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

float length(Vec3 const &v) {
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

// =============================================================================
// Vec4 length
float length_squared(Vec4 const &v) {
    return (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w);
}

float length(Vec4 const &v) {
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

// =============================================================================
// Normalizing
Vec2 normalize(Vec2 const &v) {
    Vec2 result = v;

    auto const length = length_squared(v);

    // If we're working with the zero vector or a vector that's already
    // normalized, just return
    if(length < epsilon || std::abs(length - 1.0f) < epsilon) {
        return result;
    }

    float const length_recip = 1.0f / std::sqrt(length);

    result.x *= length_recip;
    result.y *= length_recip;

    return result;
}

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

Vec4 normalize(Vec4 const &v) {
    Vec4 result = v;

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
    result.w *= length_recip;

    return result;
}

// =============================================================================
// Dot Product
float dot(Vec2 const &a, Vec2 const &b) {
    return (a.x * b.x) + (a.y * b.y);
}

float dot(Vec3 const &a, Vec3 const &b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float dot(Vec4 const &a, Vec4 const &b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

// =============================================================================
// Cross Product
Vec3 cross(Vec3 const &a, Vec3 const &b) {
    return Vec3 {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x),
    };
}

} // namespace btx::math