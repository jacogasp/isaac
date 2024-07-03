#include "physics/matrix.hpp"
#include "system/cyclic_iterator.hpp"

#include <benchmark/benchmark.h>
#include <algorithm>
#include <random>
#include <vector>

using namespace isaac;

class RandomGenerator
{
  std::uniform_real_distribution<> m_dist{-10000, 10000};
  std::mt19937 m_mt_rand;

 public:
  explicit RandomGenerator(std::random_device rd)
      : m_mt_rand(rd()) {};
  float operator()()
  {
    return m_dist(m_mt_rand);
  }
};

RandomGenerator generator{std::random_device{}};

vec3 random_vec3()
{
  return vec3{generator(), generator(), generator()};
}

template<typename Matrix>
Matrix random_mat()
{
  Matrix m{};
  std::generate(m.arr.begin(), m.arr.end(), generator);
  return m;
}

template<typename T, T Generator(void)>
std::vector<T> fill_vector(size_t size)
{
  std::vector<T> result;
  result.resize(size);
  std::generate(result.begin(), result.end(), []() { return Generator(); });
  return result;
}

constexpr size_t N_MATRICES = 10000;

auto mat2_vector{fill_vector<mat2, random_mat>(N_MATRICES)};
auto mat3_vector{fill_vector<mat3, random_mat>(N_MATRICES)};
auto mat4_vector{fill_vector<mat4, random_mat>(N_MATRICES)};
auto vec3_vector{fill_vector<vec3, random_vec3>(N_MATRICES)};

cyclic_iterator<std::vector<mat2>::iterator> mat2_iterator{mat2_vector.begin(),
                                                           mat2_vector.end()};
cyclic_iterator<std::vector<mat3>::iterator> mat3_iterator{mat3_vector.begin(),
                                                           mat3_vector.end()};
cyclic_iterator<std::vector<mat4>::iterator> mat4_iterator{mat4_vector.begin(),
                                                           mat4_vector.end()};
cyclic_iterator<std::vector<vec3>::iterator> vec3_iterator{vec3_vector.begin(),
                                                           vec3_vector.end()};

static void random_mat2(benchmark::State& state)
{
  for (auto _ : state)
    random_mat<mat2>();
}
BENCHMARK(random_mat2);

static void random_mat3(benchmark::State& state)
{
  for (auto _ : state)
    random_mat<mat3>();
}
BENCHMARK(random_mat3);

static void random_mat4(benchmark::State& state)
{
  for (auto _ : state)
    random_mat<mat4>();
}
BENCHMARK(random_mat4);

static void mult_mat2(benchmark::State& state)
{
  for (auto _ : state) {
    mat2 a = *mat2_iterator++;
    mat2 b = *mat2_iterator++;
    auto c = a * b;
  }
}
BENCHMARK(mult_mat2);

static void mult_mat3(benchmark::State& state)
{
  for (auto _ : state) {
    mat3 a = *mat3_iterator++;
    mat3 b = *mat3_iterator++;
    auto c = a * b;
  }
}
BENCHMARK(mult_mat3);

static void mult_mat4(benchmark::State& state)
{
  for (auto _ : state) {
    mat4 a = *mat4_iterator++;
    mat4 b = *mat4_iterator++;
    auto c = a * b;
  }
}
BENCHMARK(mult_mat4);

static void transpose_mat2(benchmark::State& state)
{
  for (auto _ : state) {
    mat2 m = *mat2_iterator++;
    m.transpose();
  }
}
BENCHMARK(transpose_mat2);

static void transpose_mat3(benchmark::State& state)
{
  for (auto _ : state) {
    mat3 m = *mat3_iterator++;
    m.transpose();
  }
}
BENCHMARK(transpose_mat3);

static void transpose_mat4(benchmark::State& state)
{
  for (auto _ : state) {
    mat4 m = *mat4_iterator++;
    m.transpose();
  }
}
BENCHMARK(transpose_mat4);

static void det_mat2(benchmark::State& state)
{
  for (auto _ : state) {
    mat2 m  = *mat2_iterator++;
    auto __ = m.determinant();
  }
}
BENCHMARK(det_mat2);

static void det_mat3(benchmark::State& state)
{
  for (auto _ : state) {
    mat3 m  = *mat3_iterator++;
    auto __ = m.determinant();
  }
}
BENCHMARK(det_mat3);

static void det_mat4(benchmark::State& state)
{
  for (auto _ : state) {
    mat4 m  = *mat4_iterator++;
    auto __ = m.determinant();
  }
}
BENCHMARK(det_mat4);

static void adj_mat2(benchmark::State& state)
{
  for (auto _ : state) {
    mat2 m  = *mat2_iterator++;
    auto __ = m.adjugate();
  }
}
BENCHMARK(adj_mat2);

static void adj_mat3(benchmark::State& state)
{
  for (auto _ : state) {
    mat3 m  = *mat3_iterator++;
    auto __ = m.adjugate();
  }
}
BENCHMARK(adj_mat3);

static void adj_mat4(benchmark::State& state)
{
  for (auto _ : state) {
    mat4 m  = *mat4_iterator++;
    auto __ = m.adjugate();
  }
}
BENCHMARK(adj_mat4);

static void inv_mat2(benchmark::State& state)
{
  for (auto _ : state) {
    mat2 m  = *mat2_iterator++;
    auto __ = m.inverse();
  }
}
BENCHMARK(inv_mat2);

static void inv_mat3(benchmark::State& state)
{
  for (auto _ : state) {
    mat3 m  = *mat3_iterator++;
    auto __ = m.inverse();
  }
}
BENCHMARK(inv_mat3);

static void inv_mat4(benchmark::State& state)
{
  for (auto _ : state) {
    mat4 m  = *mat4_iterator++;
    auto __ = m.inverse();
  }
}
BENCHMARK(inv_mat4);

static void scale_mat4(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::scale_matrix(*vec3_iterator++);
  }
}
BENCHMARK(scale_mat4);

static void rot_mat4(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::rotation_matrix(*vec3_iterator++);
  }
}
BENCHMARK(rot_mat4);

static void mult_mat3vec(benchmark::State& state)
{
  for (auto _ : state) {
    mat3::mult_vector(*vec3_iterator++, *mat3_iterator++);
  }
}
BENCHMARK(mult_mat3vec);

static void mult_mat4vec(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::mult_vector(*vec3_iterator++, *mat4_iterator++);
  }
}
BENCHMARK(mult_mat4vec);

static void mult_mat4point(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::mult_point(*vec3_iterator++, *mat4_iterator++);
  }
}
BENCHMARK(mult_mat4point);

static void mat4_transf_1(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::transformation_matrix(*vec3_iterator++, *vec3_iterator++,
                                *vec3_iterator++);
  }
}
BENCHMARK(mat4_transf_1);

static void mat4_transf_2(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::transformation_matrix(*vec3_iterator++, *vec3_iterator++, generator(),
                                *vec3_iterator++);
  }
}
BENCHMARK(mat4_transf_2);

static void mat4_lookAt(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::look_at(*vec3_iterator++, *vec3_iterator++, *vec3_iterator++);
  }
}
BENCHMARK(mat4_lookAt);

static void mat4_proj(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::projection(generator(), generator(), generator(), generator());
  }
}
BENCHMARK(mat4_proj);

static void mat4_ortho(benchmark::State& state)
{
  for (auto _ : state) {
    mat4::ortho(generator(), generator(), generator(), generator(), generator(),
                generator());
  }
}
BENCHMARK(mat4_ortho);

BENCHMARK_MAIN();
