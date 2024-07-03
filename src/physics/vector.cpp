#include "physics/vector.hpp"
#include "physics/math.hpp"

#include <iomanip>

namespace isaac {
// clang-format off
vec2 operator+(vec2 const & l, vec2 const& r) { return {l.x + r.x, l.y + r.y}; }
vec3 operator+(vec3 const & l, vec3 const& r) { return {l.x + r.x, l.y + r.y, l.z + r.z}; }
vec2 operator-(vec2 const & l, vec2 const& r) { return {l.x - r.x, l.y - r.y}; }
vec3 operator-(vec3 const & l, vec3 const& r) { return {l.x - r.x, l.y - r.y, l.z - r.z}; }
vec2 operator*(vec2 const & l, vec2 const& r) { return {l.x * r.x, l.y * r.y}; }
vec3 operator*(vec3 const & l, vec3 const& r) { return {l.x * r.x, l.y * r.y, l.z * r.z}; }
vec2 operator*(vec2 const& v, float k) { return {v.x * k, v.y * k}; }
vec3 operator*(vec3 const& v, float k) { return {v.x * k, v.y * k, v.z * k}; }
vec2 operator/(vec2 const& v, float k) { return {v.x / k, v.y / k}; }
vec3 operator/(vec3 const& v, float k) { return {v.x / k, v.y / k, v.z / k}; }
bool operator==(vec2 const& l, vec2 const& r) { return cmp(l.x, r.x) && cmp(l.y, r.y); }
bool operator==(vec3 const& l, vec3 const& r) { return cmp(l.x, r.x) && cmp(l.y, r.y) && cmp(l.z, r.z); }
bool operator!=(vec2 const& l, vec2 const& r) { return !(l == r); }
bool operator!=(vec3 const& l, vec3 const& r) { return !(l == r); }
vec2& vec2::operator+=(vec2 const& other) { x += other.x; y += other.y; return *this; }
vec2& vec2::operator-=(vec2 const& other) { x -= other.x; y -= other.y; return *this; }
vec2& vec2::operator*=(vec2 const& other) { x *= other.x; y *= other.y; return *this; }
vec2& vec2::operator/=(float k) { x /= k; y /= k; return *this; }
vec3& vec3::operator+=(vec3 const& other) { x += other.x; y += other.y; z += other.z; return *this; }
vec3& vec3::operator-=(vec3 const& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
vec3& vec3::operator*=(vec3 const& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
vec3& vec3::operator/=(float k) { x /= k; y /= k; z /= k; return *this; }
// clang-format on

namespace vec {
float dot(vec2 const& l, vec2 const& r)
{
  return l.x * r.x + l.y * r.y;
}
float dot(vec3 const& l, vec3 const& r)
{
  return l.x * r.x + l.y * r.y + l.z * r.z;
};
vec3 cross(vec3 const& l, vec3 const& r)
{
  return {l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x};
}
} // namespace vec

// clang-format off
float vec2::dot(vec2 const& other) const { return vec::dot(*this, other); }
float vec3::dot(vec3 const& other) const { return vec::dot(*this, other); }
vec3 vec3::cross(vec3 const& other) const { return vec::cross(*this, other); }
float vec2::magnitude() const { return vec::magnitude(*this); }
float vec3::magnitude() const { return vec::magnitude(*this); }
float vec2::magnitude_sq() const { return vec::magnitude_sq(*this); }
float vec3::magnitude_sq() const { return vec::magnitude_sq(*this); }
float vec2::distance(vec2 const& other) const { return vec::distance(*this, other); }
float vec3::distance(vec3 const& other) const { return vec::distance(*this, other); }
void vec2::normalize() { vec::normalize(*this); }
vec2 vec2::normalized() const { return vec::normalized(*this); }
void vec3::normalize() { vec::normalize(*this); }
vec3 vec3::normalized() const { return vec::normalized(*this); }
float vec2::angle(vec2 const& other) const { return vec::angle(*this, other); }
float vec3::angle(vec3 const& other) const { return vec::angle(*this, other); }
vec2 vec2::project(vec2 const& other) const { return vec::project(*this, other); }
vec3 vec3::project(vec3 const& other) const { return vec::project(*this, other); }
vec2 vec2::perpendicular(vec2 const& other) const { return vec::perpendicular(*this, other); }
vec3 vec3::perpendicular(vec3 const& other) const { return vec::perpendicular(*this, other); }
vec2 vec2::reflect(vec2 const& norm) const { return vec::reflection(*this, norm); }
vec3 vec3::reflect(vec3 const& norm) const { return vec::reflection(*this, norm); }
// clang-format on

std::ostream& operator<<(std::ostream& o, vec2 const& v)
{
  o << std::fixed << std::setprecision(8) << "[" << v.x << ", " << v.y << "]";
  return o;
}
std::ostream& operator<<(std::ostream& o, vec3 const& v)
{
  o << std::fixed << std::setprecision(8) << "[" << v.x << ", " << v.y << ", "
    << v.z << "]";
  return o;
}
} // namespace isaac
