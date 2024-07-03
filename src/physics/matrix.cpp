#include "physics/matrix.hpp"
#include "system/thread.hpp"

#include <thread>

namespace isaac {

// Matrix 2x2
std::ostream& operator<<(std::ostream& out, mat2 const& matrix)
{
  print_matrix(out, matrix, 2);
  return out;
}

bool operator==(mat2 const& l, mat2 const& r)
{
  return matrix_cmp(l, r);
}

void mat2::transpose()
{
  data_t<4> result{};
  ::isaac::transpose<2, 2>(result, arr);
  arr = result;
}

mat2 mat2::transposed() const
{
  mat2 result{};
  ::isaac::transpose<2, 2>(result.arr, arr);
  return result;
}

mat2 operator*(mat2 const& mat, float scalar)
{
  mat2 result;
  mult_scalar(result.arr, mat.arr, scalar);
  return result;
}

mat2 operator*(mat2 const& l, mat2 const& r)
{
  mat2 result;
  mult_array<2, 2, 2, 2>(result.arr, l.arr, r.arr);
  return result;
}

mat2 mat2::minor() const
{
  return mat2{_22, _21, _12, _11};
}
mat2 mat2::cofactor() const
{
  return cofactor<mat2, 2, 2>(*this);
}
float mat2::determinant() const
{
  return _11 * _22 - _12 * _21;
}
mat2 mat2::adjugate() const
{
  return ::isaac::adjugate(*this);
}
mat2 mat2::inverse() const
{
  return ::isaac::inverse(*this);
}

// ---------------------
// Matrix 3x3

std::ostream& operator<<(std::ostream& out, mat3 const& matrix)
{
  print_matrix(out, matrix, 3);
  return out;
}

void mat3::transpose()
{
  data_t<9> result{};
  ::isaac::transpose<3, 3>(result, arr);
  arr = result;
}

mat3 mat3::transposed() const
{
  mat3 result{};
  ::isaac::transpose<3, 3>(result.arr, arr);
  return result;
}

mat2 mat3::cut(int row, int col) const
{
  mat2 result;
  ::isaac::cut<3, 3>(result.arr, arr, row, col);
  return result;
}

mat3 operator*(mat3 const& mat, float scalar)
{
  mat3 result;
  mult_scalar(result.arr, mat.arr, scalar);
  return result;
}

mat3 operator*(mat3 const& l, mat3 const& r)
{
  mat3 result;
  mult_array<3, 3, 3, 3>(result.arr, l.arr, r.arr);
  return result;
}

mat3 mat3::cofactor() const
{
  return cofactor<mat3, 3, 3>(*this);
}
mat3 mat3::minor() const
{
  return minor<mat3, 3, 3>(*this);
}
float mat3::determinant() const
{
  return determinant<mat3, 3>(*this);
}
mat3 mat3::adjugate() const
{
  return ::isaac::adjugate(*this);
}
mat3 mat3::inverse() const
{
  return ::isaac::inverse(*this);
}

bool operator==(mat3 const& l, mat3 const& r)
{
  return matrix_cmp(l, r);
}

mat3 mat3::rotation_matrix(float pitch, float yaw, float roll)
{
  return rotation_X(pitch) * rotation_Y(yaw) * rotation_Z(roll);
}

mat3 mat3::rotation_matrix(vec3 const& angles)
{
  return rotation_matrix(angles.x, angles.y, angles.z);
}

mat3 mat3::rotation_X(float angle)
{
  mat3 m;
  m._22 = std::cos(angle);
  m._23 = std::sin(angle);
  m._32 = -std::sin(angle);
  m._33 = std::cos(angle);
  return m;
}

mat3 mat3::rotation_Y(float angle)
{
  mat3 m;
  m._11 = std::cos(angle);
  m._13 = -std::sin(angle);
  m._31 = std::sin(angle);
  m._33 = std::cos(angle);
  return m;
}
mat3 mat3::rotation_Z(float angle)
{
  mat3 m;
  m._11 = std::cos(angle);
  m._12 = std::sin(angle);
  m._21 = -std::sin(angle);
  m._22 = std::cos(angle);
  return m;
}

mat3 mat3::rotation_matrix(vec3 const& rotationAxis, float angle)
{
  float c = std::cos(angle);
  float s = std::sin(angle);
  float t = 1.0f - c;

  float x = rotationAxis.x;
  float y = rotationAxis.y;
  float z = rotationAxis.z;

  if (!cmp(rotationAxis.magnitude(), 1.0f)) {
    auto inv_mag = 1.0f / rotationAxis.magnitude();
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
  }
  return mat3{
      t * x * x + c,     t * x * y + s * z, t * x * z - s * y,
      t * x * y - s * z, t * y * y + c,     t * y * z + s * x,
      t * x * z + s * y, t * y * z - s * x, t * z * z + c,
  };
}

vec3 mat3::mult_vector(vec3 const& vec, mat3 const& mat)
{
  vec3 result{};
  result.x = vec.dot(vec3{mat._11, mat._21, mat._31});
  result.y = vec.dot(vec3{mat._12, mat._22, mat._32});
  result.z = vec.dot(vec3{mat._13, mat._23, mat._33});
  return result;
}

// ---------------------
// Matrix 4x4

std::ostream& operator<<(std::ostream& out, mat4 const& matrix)
{
  print_matrix(out, matrix, 4);
  return out;
}

void mat4::transpose()
{
  data_t<16> result{};
  ::isaac::transpose<4, 4>(result, arr);
  arr = result;
}

mat4 mat4::transposed() const
{
  mat4 result{};
  ::isaac::transpose<4, 4>(result.arr, arr);
  return result;
}

mat3 mat4::cut(int row, int col) const
{
  mat3 result;
  ::isaac::cut<4, 4>(result.arr, arr, row, col);
  return result;
}

mat4 operator*(mat4 const& mat, float scalar)
{
  mat4 result;
  mult_scalar(result.arr, mat.arr, scalar);
  return result;
}

mat4 operator*(mat4 const& l, mat4 const& r)
{
  mat4 result;
  mult_array<4, 4, 4, 4>(result.arr, l.arr, r.arr);
  return result;
}

mat4 mat4::minor() const
{
  return minor<mat4, 4, 4>(*this);
}
mat4 mat4::cofactor() const
{
  return cofactor<mat4, 4, 4>(*this);
}
float mat4::determinant() const
{
  return determinant<mat4, 4>(*this);
}
mat4 mat4::adjugate() const
{
  return ::isaac::adjugate(*this);
}
mat4 mat4::inverse() const
{
  return ::isaac::inverse(*this);
}
bool operator==(mat4 const& l, mat4 const& r)
{
  return matrix_cmp(l, r);
}

mat4 mat4::translation(float x, float y, float z)
{
  mat4 m;
  m._41 = x;
  m._42 = y;
  m._43 = z;
  return m;
}

mat4 mat4::translation(vec3 const& pos)
{
  mat4 m;
  m._41 = pos.x;
  m._42 = pos.y;
  m._43 = pos.z;
  return m;
}
vec3 mat4::get_translation() const
{
  return vec3{_41, _42, _43};
}

mat4 mat4::scale_matrix(float x, float y, float z)
{
  mat4 m;
  m._11 = x;
  m._22 = y;
  m._33 = z;
  return m;
}

mat4 mat4::scale_matrix(vec3 const& magnitude)
{
  mat4 m;
  m._11 = magnitude.x;
  m._22 = magnitude.y;
  m._33 = magnitude.z;
  return m;
}

vec3 mat4::get_scale() const
{
  return vec3{_11, _22, _33};
}

mat4 mat4::rotation_matrix(float pitch, float yaw, float roll)
{
  return rotation_X(pitch) * rotation_Y(yaw) * rotation_Z(roll);
}

inline mat4 mat4::rotation_matrix(vec3 const& angles)
{
  return rotation_matrix(angles.x, angles.y, angles.z);
}

mat4 mat4::rotation_X(float angle)
{
  mat4 m;
  m._22 = std::cos(angle);
  m._23 = std::sin(angle);
  m._32 = -std::sin(angle);
  m._33 = std::cos(angle);
  return m;
}

mat4 mat4::rotation_Y(float angle)
{
  mat4 m;
  m._11 = std::cos(angle);
  m._13 = -std::sin(angle);
  m._31 = std::sin(angle);
  m._33 = std::cos(angle);
  return m;
}
mat4 mat4::rotation_Z(float angle)
{
  mat4 m;
  m._11 = std::cos(angle);
  m._12 = std::sin(angle);
  m._21 = -std::sin(angle);
  m._22 = std::cos(angle);
  return m;
}

mat4 mat4::rotation_matrix(vec3 const& rotation_axis, float angle)
{
  float c = std::cos(angle);
  float s = std::sin(angle);
  float t = 1.0f - c;

  float x = rotation_axis.x;
  float y = rotation_axis.y;
  float z = rotation_axis.z;

  if (!cmp(rotation_axis.magnitude(), 1.0f)) {
    auto inv_mag = 1.0f / rotation_axis.magnitude();
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
  }
  return mat4{t * x * x + c,
              t * x * y + s * z,
              t * x * z - s * y,
              0.0f,
              t * x * y - s * z,
              t * y * y + c,
              t * y * z + s * x,
              0.0f,
              t * x * z - s * y,
              t * y * z - s * x,
              t * z * z + c,
              0.0f,
              0.0f,
              0.0f,
              0.0f,
              1.0f};
}

void _multi_point(vec3& p, mat4 const& mat)
{
  p.x = p.x * mat._11 + p.y * mat._21 + p.z * mat._31 + mat._41;
  p.y = p.x * mat._12 + p.y * mat._22 + p.z * mat._32 + mat._42;
  p.z = p.z * mat._13 + p.y * mat._13 + p.z * mat._33 + mat._43;
}

vec3 mat4::mult_point(vec3 const& point, mat4 const& mat)
{
  vec3 result{point};
  _multi_point(result, mat);
  return result;
}

vec3 mat4::mult_vector(vec3 const& vec, mat4 const& mat)
{
  vec3 result{};
  result.x = vec.x * mat._11 + vec.y * mat._21 + vec.z * mat._31 + mat._41;
  result.y = vec.x * mat._12 + vec.y * mat._22 + vec.z * mat._32 + mat._42;
  result.x = vec.x * mat._13 + vec.y * mat._23 + vec.z * mat._33 + mat._43;
  return result;
}

mat4 mat4::transformation_matrix(vec3 const& scale, vec3 const& euler_rotation,
                                 vec3 const& translate)
{
  return mat4::scale_matrix(scale) * mat4::rotation_matrix(euler_rotation)
       * translation(translate);
}

mat4 mat4::transformation_matrix(vec3 const& scale, vec3 const& rotation_axis,
                                 float angle, vec3 const& translate)
{
  return rotation_matrix(rotation_axis, angle) * mat4::scale_matrix(scale)
       * translation(translate);
}

mat4 mat4::look_at(vec3 const& position, vec3 const& target, vec3 const& up)
{
  vec3 forward{target - position};
  forward.normalize();
  vec3 right{up.cross(forward)};
  right.normalize();
  vec3 newUp{forward.cross(right)};

  return mat4{right.x,
              newUp.x,
              forward.x,
              0.0f,
              right.y,
              newUp.y,
              forward.y,
              0.0f,
              right.z,
              newUp.z,
              forward.z,
              0.0f,
              -right.dot(position),
              -newUp.dot(position),
              -forward.dot(position),
              1.0f};
}

mat4 mat4::projection(float fov, float aspect, float z_near, float z_far)
{
  float tan_half_fov = std::tan(fov * 0.5f);
  float fov_Y        = 1.0f / tan_half_fov;
  float fov_X        = fov_Y / aspect;
  mat4 result;
  result._11 = fov_X;
  result._22 = fov_Y;
  result._33 = z_near / (z_far - z_near);
  result._34 = 1.0f;
  result._43 = -z_near * result._33;
  result._34 = 0.0f;
  return result;
}

mat4 mat4::ortho(float left, float right, float bottom, float top, float zNear,
                 float zFar)
{
  float _11 = 2.0f / (right - left);
  float _22 = 2.0f / (top - bottom);
  float _33 = 1.0f / (zFar - zNear);
  float _41 = (left + right) / (left - right);
  float _42 = (top + bottom) / (bottom - top);
  float _43 = zNear / (zNear - zFar);
  return mat4{_11, 0, 0, 0, 0, _22, 0, 0, 0, 0, _33, 0, _41, _42, _43, 1};
}

vec2 mult(vec2 const& v, mat2 const& m)
{
  vec2 r{};
  mult_array<2, 1, 2, 2>(r.arr, v.arr, m.arr);
  return r;
}
} // namespace isaac
