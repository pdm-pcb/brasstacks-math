#include "brasstacks/math/math.hpp"
#include "brasstacks/math/Vec4.hpp"

namespace btx::math {

// =============================================================================
bool Vec4::operator==(const Vec4 &other) const {
    // If the absolute value of the difference between this.x and other.x is
    // less than the chosen float epsilon, then the x components of the two
    // vectors are the same. If all members hit this criterion, the vectors are
    // equal.

    return (
        std::abs(x - other.x) < epsilon &&
        std::abs(y - other.y) < epsilon &&
        std::abs(z - other.z) < epsilon &&
        std::abs(w - other.w) < epsilon
    );
}

Vec4 Vec4::operator+(Vec4 const &other) const {
    return { x + other.x, y + other.y, z + other.z, w + other.w };
}

Vec4 Vec4::operator-(Vec4 const &other) const {
    return { x - other.x, y - other.y, z - other.z, w - other.w };
}

Vec4 Vec4::operator-() const {
    return { -x, -y, -z, -w };
}

Vec4 & Vec4::operator+=(Vec4 const &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vec4 & Vec4::operator-=(Vec4 const &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vec4 & Vec4::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vec4 & Vec4::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

// =============================================================================
Vec4 operator*(float scalar, Vec4 const &v) {
    return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar };
}

Vec4 operator*(Vec4 const &v, float scalar) {
    return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar };
}

Vec4 operator/(Vec4 const &v, float scalar) {
    return { v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar };
}

// =============================================================================
Vec4::Vec4(float x, float y, float z, float w) :
    x { x },
    y { y },
    z { z },
    w { w }
{ }

// =============================================================================
std::ostream & operator<<(std::ostream& out, Vec4 const& v) {
    out << std::fixed << std::setprecision(print_precs)
        << std::setw(print_width) << v.x << " "
        << std::setw(print_width) << v.y << " "
        << std::setw(print_width) << v.z;

    return out;
}

} // namespace btx::math