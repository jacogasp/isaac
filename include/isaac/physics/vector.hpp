#ifndef PHYSICS_VECTOR_HPP
#define PHYSICS_VECTOR_HPP

#include <array>
#include <cmath>
#include <iostream>

namespace isaac {
inline float rad2deg(float x)
{
  return x * 57.295754f;
}
inline float deg2rad(float x)
{
  return x * 0.0174533f;
}

struct vec2
{
  std::array<float, 2> arr{};
  float& x = arr[0];
  float& y = arr[1];
  vec2()   = default;
  vec2(float _x, float _y)
      : arr{_x, _y} {};
  vec2(vec2 const& other)
  {
    arr = other.arr;
  }
  vec2& operator=(vec2 const& other)
  {
    arr = other.arr;
    return *this;
  }

  [[nodiscard]] float dot(vec2 const& other) const;
  [[nodiscard]] float magnitude() const;
  [[nodiscard]] float magnitude_sq() const;
  [[nodiscard]] float distance(vec2 const& other) const;
  [[nodiscard]] float angle(vec2 const& other) const;
  [[nodiscard]] vec2 project(vec2 const& other) const;
  [[nodiscard]] vec2 perpendicular(vec2 const& other) const;
  [[nodiscard]] vec2 reflect(vec2 const& norm) const;
  [[nodiscard]] vec2 normalized() const;
  vec2& operator+=(vec2 const& other);
  vec2& operator-=(vec2 const& other);
  vec2& operator*=(vec2 const& other);
  vec2& operator/=(float k);
  void normalize();
};

struct vec3
{
  std::array<float, 3> arr{};
  float& x = arr[0];
  float& y = arr[1];
  float& z = arr[2];
  vec3()   = default;
  vec3(float _x, float _y, float _z)
      : arr{_x, _y, _z} {};
  vec3(vec3 const& other)
  {
    arr = other.arr;
  }
  vec3& operator=(vec3 const& other)
  {
    arr = other.arr;
    return *this;
  }
  [[nodiscard]] float dot(vec3 const& other) const;
  [[nodiscard]] float magnitude() const;
  [[nodiscard]] float magnitude_sq() const;
  [[nodiscard]] float distance(vec3 const& other) const;
  [[nodiscard]] vec3 cross(vec3 const& other) const;
  [[nodiscard]] float angle(vec3 const& other) const;
  [[nodiscard]] vec3 project(vec3 const& other) const;
  [[nodiscard]] vec3 perpendicular(vec3 const& other) const;
  [[nodiscard]] vec3 reflect(vec3 const& norm) const;
  [[nodiscard]] vec3 normalized() const;
  vec3& operator+=(vec3 const& other);
  vec3& operator-=(vec3 const& other);
  vec3& operator*=(vec3 const& other);
  vec3& operator/=(float k);
  void normalize();
};

vec2 operator+(vec2 const& l, vec2 const& r);
vec2 operator-(vec2 const& l, vec2 const& r);
vec2 operator*(vec2 const& l, vec2 const& r);
vec2 operator*(vec2 const& v, float k);
vec2 operator/(vec2 const& v, float k);
bool operator==(vec2 const& l, vec2 const& r);
bool operator!=(vec2 const& l, vec2 const& r);

vec3 operator+(vec3 const& l, vec3 const& r);
vec3 operator-(vec3 const& l, vec3 const& r);
vec3 operator*(vec3 const& l, vec3 const& r);
vec3 operator*(vec3 const& v, float k);
vec3 operator/(vec3 const& v, float k);
bool operator==(vec3 const& l, vec3 const& r);
bool operator!=(vec3 const& l, vec3 const& r);

namespace vec {
float dot(vec2 const& l, vec2 const& r);
float dot(vec3 const& l, vec3 const& r);
vec3 cross(vec3 const& l, vec3 const& r);

template<typename T>
float magnitude(T const& x)
{
  return std::sqrt(dot(x, x));
}

template<typename T>
float magnitude_sq(T const& x)
{
  return dot(x, x);
}

template<typename T>
float distance(T const& p1, T const& p2)
{
  T t{p1 - p2};
  return magnitude(t);
}

template<typename T>
void normalize(T& v)
{
  v = v / magnitude(v);
}

template<typename T>
T normalized(T& v)
{
  return v / magnitude(v);
}

template<typename T>
float angle(T const& l, T const& r)
{
  float m = std::sqrt(magnitude_sq(l) * magnitude_sq(r));
  return std::acos(dot(l, r) / m);
}

template<typename T>
T project(T const& length, T const& direction)
{
  return direction * dot(length, direction) / magnitude_sq(direction);
}

template<typename T>
T perpendicular(T const& length, T const& direction)
{
  return length - project(length, direction);
}

template<typename T>
T reflection(T const& v, T const& normal)
{
  float d = dot(v, normal);
  return v - normal * (d * 2.0f);
}
} // namespace vec

std::ostream& operator<<(std::ostream& o, vec2 const& v);
std::ostream& operator<<(std::ostream& o, vec3 const& v);
} // namespace isaac

#endif