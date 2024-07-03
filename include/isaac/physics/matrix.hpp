#ifndef PHYSICS_MATRIX_HPP
#define PHYSICS_MATRIX_HPP

#include "math.hpp"
#include "vector.hpp"
#include "system/thread.hpp"

#include <array>
#include <cassert>
#include <functional>
#include <iomanip>
#include <variant>

namespace isaac {
template<size_t S>
using data_t = std::array<float, S>;

struct mat2
{
  std::array<float, 4> arr{1.0f, 0.0f, 0.0f, 1.0f};

  float& _11 = arr[0];
  float& _12 = arr[1];
  float& _21 = arr[2];
  float& _22 = arr[3];

  inline mat2() = default;
  inline mat2(float f11, float f12, float f21, float f22)
      : arr{f11, f12, f21, f22} {};
  mat2(mat2 const& other)
  {
    arr = other.arr;
  }
  mat2& operator=(mat2 const& other)
  {
    arr = other.arr;
    return *this;
  }
  inline float* operator[](int i)
  {
    return &(arr[i * 2]);
  }

  void transpose();
  [[nodiscard]] mat2 transposed() const;
  [[nodiscard]] mat2 minor() const;
  [[nodiscard]] mat2 cofactor() const;
  [[nodiscard]] float determinant() const;
  [[nodiscard]] mat2 adjugate() const;
  [[nodiscard]] mat2 inverse() const;
};

struct mat3
{
  std::array<float, 9> arr{1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                           0.0f, 0.0f, 0.0f, 1.0f};
  float& _11 = arr[0];
  float& _12 = arr[1];
  float& _13 = arr[2];
  float& _21 = arr[3];
  float& _22 = arr[4];
  float& _23 = arr[5];
  float& _31 = arr[6];
  float& _32 = arr[7];
  float& _33 = arr[8];

  inline mat3() = default;
  inline mat3(float f11, float f12, float f13, float f21, float f22, float f23,
              float f31, float f32, float f33)
      : arr{f11, f12, f13, f21, f22, f23, f31, f32, f33}
  {}
  mat3(mat3 const& other)
  {
    arr = other.arr;
  }
  mat3& operator=(mat3 const& other)
  {
    arr = other.arr;
    return *this;
  }
  inline float* operator[](int i)
  {
    return &(arr[i * 3]);
  }
  void transpose();
  [[nodiscard]] mat3 transposed() const;
  [[nodiscard]] mat2 cut(int row, int col) const;
  [[nodiscard]] mat3 minor() const;
  [[nodiscard]] mat3 cofactor() const;
  [[nodiscard]] float determinant() const;
  [[nodiscard]] mat3 adjugate() const;
  [[nodiscard]] mat3 inverse() const;
  static mat3 rotation_matrix(float pitch, float yaw, float roll);
  static mat3 rotation_matrix(vec3 const& rotationAxis, float angle);
  static mat3 rotation_matrix(vec3 const& angles);
  static mat3 rotation_X(float angle);
  static mat3 rotation_Y(float angle);
  static mat3 rotation_Z(float angle);
  static vec3 mult_vector(vec3 const& vec, mat3 const& mat);
};

struct mat4
{
  std::array<float, 16> arr{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

  float& _11 = arr[0];
  float& _12 = arr[1];
  float& _13 = arr[2];
  float& _14 = arr[3];
  float& _21 = arr[4];
  float& _22 = arr[5];
  float& _23 = arr[6];
  float& _24 = arr[7];
  float& _31 = arr[8];
  float& _32 = arr[9];
  float& _33 = arr[10];
  float& _34 = arr[11];
  float& _41 = arr[12];
  float& _42 = arr[13];
  float& _43 = arr[14];
  float& _44 = arr[15];

  inline mat4() = default;
  inline mat4(float f11, float f12, float f13, float f14, float f21, float f22,
              float f23, float f24, float f31, float f32, float f33, float f34,
              float f41, float f42, float f43, float f44)
      : arr{f11, f12, f13, f14, f21, f22, f23, f24,
            f31, f32, f33, f34, f41, f42, f43, f44}
  {}
  mat4(mat4 const& other)
  {
    arr = other.arr;
  }
  mat4& operator=(mat4 const& other)
  {
    arr = other.arr;
    return *this;
  }
  inline float* operator[](int i)
  {
    return &(arr[i * 4]);
  }
  void transpose();
  [[nodiscard]] mat4 transposed() const;
  [[nodiscard]] mat3 cut(int row, int col) const;
  [[nodiscard]] mat4 minor() const;
  [[nodiscard]] mat4 cofactor() const;
  [[nodiscard]] float determinant() const;
  [[nodiscard]] mat4 adjugate() const;
  [[nodiscard]] mat4 inverse() const;
  static mat4 translation(float x, float y, float z);
  static mat4 translation(vec3 const& pos);
  [[nodiscard]] vec3 get_translation() const;
  static mat4 scale_matrix(float x, float y, float z);
  static mat4 scale_matrix(vec3 const& magnitude);
  [[nodiscard]] vec3 get_scale() const;
  static mat4 rotation_matrix(float pitch, float yaw, float roll);
  static mat4 rotation_matrix(vec3 const& rotation_axis, float angle);
  static mat4 rotation_matrix(vec3 const& angles);
  static mat4 rotation_X(float angle);
  static mat4 rotation_Y(float angle);
  static mat4 rotation_Z(float angle);
  static vec3 mult_point(vec3 const& point, mat4 const& mat);
  static vec3 mult_vector(vec3 const& vec, mat4 const& mat);
  static mat4 transformation_matrix(vec3 const& scale,
                                    vec3 const& euler_rotation,
                                    vec3 const& translate);
  static mat4 transformation_matrix(vec3 const& scale,
                                    vec3 const& rotation_axis, float angle,
                                    vec3 const& translate);
  static mat4 look_at(vec3 const& position, vec3 const& target, vec3 const& up);
  static mat4 projection(float fov, float aspect, float z_near, float z_far);
  static mat4 ortho(float left, float right, float bottom, float top,
                    float z_near, float z_far);
};

std::ostream& operator<<(std::ostream& out, mat2 const& l);
std::ostream& operator<<(std::ostream& out, mat3 const& l);
std::ostream& operator<<(std::ostream& out, mat4 const& l);
bool operator==(mat2 const& l, mat2 const& r);
bool operator==(mat3 const& l, mat3 const& r);
bool operator==(mat4 const& l, mat4 const& r);
mat2 operator*(mat2 const& l, float scalar);
mat3 operator*(mat3 const& l, float scalar);
mat4 operator*(mat4 const& l, float scalar);
mat2 operator*(mat2 const& l, mat2 const& r);
mat3 operator*(mat3 const& l, mat3 const& r);
mat4 operator*(mat4 const& l, mat4 const& r);

vec2 mult(vec2 const& v, mat2 const& m);

// ---------------------
// Common functions

template<typename T>
inline std::ostream& print_matrix(std::ostream& out, T const& matrix,
                                  size_t rows)
{
  for (size_t i = 0; i < matrix.arr.size(); i++) {
    out << std::fixed << std::setprecision(8) << matrix.arr.at(i) << '\t';
    if ((i + 1) % rows == 0)
      out << '\n';
  }
  return out;
}

template<size_t Rows, size_t Cols>
void transpose(data_t<Rows * Cols>& out, data_t<Rows * Cols> arr)
{
  for (size_t i = 0; i < Rows * Cols; ++i) {
    int row = i / Rows;
    int col = i % Cols;
    out[i]  = arr[Cols * col + row];
  }
}

// Multiplications
template<size_t S>
void mult_scalar(data_t<S>& out, data_t<S> const& arr, float scalar)
{
  for (size_t i = 0; i < arr.size(); ++i)
    out[i] = arr.at(i) * scalar;
}

template<size_t ColsA, size_t RowsA, size_t ColsB, size_t RowsB>
void mult_array(data_t<RowsA * ColsB>& out, data_t<ColsA * RowsA> const& A,
                std::array<float, ColsB * RowsB> const& B)
{
  assert(ColsA == RowsB);
  for (size_t i = 0; i < RowsA; ++i) {
    for (size_t j = 0; j < ColsB; ++j) {
      out[ColsB * i + j] = 0.0f;
      for (size_t k = 0; k < RowsB; ++k) {
        int a = ColsA * i + k;
        int b = ColsB * k + j;
        out.at(ColsB * i + j) += A[a] * B[b];
      }
    }
  }
}

// determinant
template<typename T, size_t Rows, size_t Cols>
T cofactor(T const& matrix)
{
  T result;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      size_t index         = Cols * j + i;
      float sign           = std::powf(-1.0f, (float)(i + j));
      result.arr.at(index) = matrix.minor().arr.at(index) * sign;
    }
  }
  return result;
}

template<typename T, size_t Rows, size_t Cols>
T minor(T const& matrix)
{
  T result{};
  for (size_t i = 0; i < Rows; ++i)
    for (size_t j = 0; j < Cols; ++j) {
      auto cut     = matrix.cut(i, j);
      result[i][j] = cut.determinant();
    }
  return result;
}

template<typename T, size_t Rows>
float determinant(T const& matrix)
{
  float result  = 0.0f;
  auto cofactor = matrix.cofactor();
  for (size_t j = 0; j < Rows; ++j)
    result += matrix.arr[j] * cofactor[0][j];
  return result;
}

template<typename T>
T adjugate(T const& matrix)
{
  T result = matrix.cofactor();
  result.transpose();
  return result;
}

template<typename T>
T inverse(T const& matrix)
{
  float det = matrix.determinant();
  if (cmp(det, 0.0f)) {
    return T{};
  }
  return matrix.adjugate() * (1.0f / det);
}

inline mat4 inverse(mat4 const& matrix)
{
  mat4 adj;
  thread_guard t{[&adj, &matrix]() { adj = matrix.adjugate(); }};
  float det = matrix.determinant();
  t.join();
  if (cmp(det, 0.0f)) {
    return mat4{};
  }
  return adj * (1.0f / det);
}

template<class T>
bool matrix_cmp(T const& l, T const& r)
{
  bool equal = true;
  {
    for (size_t i = 0; i < l.arr.size(); i++)
      equal &= cmp(l.arr.at(i), r.arr.at(i));
  }
  return equal;
}

/// Cut a MxN matrix in a M-1xN-1 matrix, deleting the provided row and column
template<size_t Rows, size_t Cols>
void cut(data_t<(Rows - 1) * (Cols - 1)>& out, data_t<Rows * Cols> const arr,
         size_t row, size_t col)
{
  size_t index = 0;
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      if (i == row || j == col) {
        continue;
      }
      size_t target  = index++;
      size_t source  = Rows * i + j;
      out.at(target) = arr.at(source);
    }
  }
}

} // namespace isaac
#endif
