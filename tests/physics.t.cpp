#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "physics/geometry_2d.hpp"
#include "physics/matrix.hpp"
#include "physics/quad_tree.hpp"
#include "physics/vector.hpp"

#include "doctest.h"

#include <iomanip>
#include <iostream>
#include <variant>

using namespace isaac::vec;
using namespace isaac;

struct Float
{
  float x;

  Float() = default;

  explicit Float(float x_)
      : x{x_} {};

  Float& operator=(float x_)
  {
    x = x_;
    return *this;
  }

  bool operator==(Float const& other) const
  {
    return cmp(x, other.x);
  }
};

std::ostream& operator<<(std::ostream& o, Float const& f)
{
  o << std::fixed << std::setprecision(8) << f.x;
  return o;
}

TEST_SUITE_BEGIN("Utils Test Suite");
TEST_CASE("Utils")
{
  CHECK_EQ(Float(clamp(0.6f, 0.0f, 1.0f)), Float{0.6});
  CHECK_EQ(Float(clamp(-3.4f, 0.0f, 1.0f)), Float{0});
  CHECK_EQ(Float(clamp(5.4f, 0.0f, 1.0f)), Float{1});
  CHECK_EQ(Float(clamp(3.2f, -2.4f, 4.5f)), Float{3.2f});
  CHECK_EQ(Float(clamp(-5.3f, -2.4f, 4.5f)), Float{-2.4f});
  CHECK_EQ(Float(clamp(5.3f, -2.4f, 4.5f)), Float{4.5f});
}
TEST_SUITE_END;

TEST_SUITE_BEGIN("Vector Test Suite");

TEST_CASE("Vectors 2D")
{
  vec2 v1{1.0f, -4.2f};
  vec2 v2{-5.0f, 9.3f};
  vec2 v3{};

  std::cout << "v1: " << v1 << '\n';
  std::cout << "v2: " << v2 << '\n';

  CHECK_EQ(v1, v1);
  CHECK_NE(v1, v2);

  v3 = v1;
  v3 += v2;
  CHECK_EQ(v3, vec2{-4.0, 5.1});
  v3 = v1;
  v3 -= v2;
  CHECK_EQ(v3, vec2{6.0, -13.5});
  v3 = v1;
  v3 *= v2;
  CHECK_EQ(v3, vec2{-5.0, -39.06});
  v3 = v1;
  v3 /= 3.5;
  CHECK_EQ(v3, vec2{0.2857142857, -1.2});

  CHECK_EQ(Float{dot(v1, v2)}, Float{-44.06f});
  CHECK_EQ(Float{v1.dot(v2)}, Float{-44.06f});
  CHECK_EQ(Float{v1.magnitude()}, Float{4.3174066f});
  CHECK_EQ(Float{v2.magnitude_sq()}, Float{111.49f});
  CHECK_EQ(Float{v1.distance(v2)}, Float{14.7732867027f});
  auto v1_copy = v1;
  v1_copy.normalize();
  CHECK_EQ(v1_copy, vec2{0.2316205273f, -0.9728062147f});
  auto v2_norm = v2.normalized();
  CHECK_EQ(v2_norm, vec2{-0.473534959, 0.8807750238f});
  float angle = v1.angle(v2);
  CHECK_EQ(Float{angle}, Float{2.8820357f});
  CHECK_EQ(Float{rad2deg(angle)}, Float{165.128403f});
  CHECK_EQ(Float{deg2rad(rad2deg(angle))}, Float{angle});
  CHECK_EQ(v1.project(v2), vec2{1.97596180f, -3.67528915f});
  CHECK_EQ(v1.perpendicular(v2), vec2{-0.97596180f, -0.52471066f});
  CHECK_EQ(v1.reflect(v2.normalized()), vec2{-2.95192385f, 3.15057898f});

  CHECK_EQ(mult(vec2{-4, 2}, mat2{3, 4, 5, 6}), vec2{-2, -4});
}

TEST_CASE("Vectors 3D")
{
  vec3 v1{1.0f, -4.2f, 5.2f};
  vec3 v2{-5.0f, 9.3f, -4.2f};
  vec3 v3{};

  std::cout << "v1: " << v1 << '\n';
  std::cout << "v2: " << v2 << '\n';

  CHECK_EQ(v1, v1);
  CHECK_NE(v1, v2);
  CHECK_EQ(v1 + v2, vec3{-4.0, 5.1, 1.0});
  CHECK_EQ(v1 - v2, vec3{6.0, -13.5, 9.4});
  CHECK_EQ(v1 * v2, vec3{-5.0, -39.06, -21.84});
  v3 = v1;
  v3 += v2;
  CHECK_EQ(v3, vec3{-4.0, 5.1, 1.0});
  v3 = v1;
  v3 -= v2;
  CHECK_EQ(v3, vec3{6.0, -13.5, 9.4});
  v3 = v1;
  v3 *= v2;
  CHECK_EQ(v3, vec3{-5.0, -39.06, -21.84});
  v3 = v1;
  v3 /= 3.5;
  CHECK_EQ(v3, vec3{0.2857142857, -1.2, 1.4857142857});
  CHECK_EQ(Float{dot(v1, v2)}, Float{-65.9f});
  CHECK_EQ(Float{v1.dot(v2)}, Float{-65.9f});
  CHECK_EQ(Float{v1.magnitude()}, Float{6.75869801f});
  CHECK_EQ(Float{v2.magnitude_sq()}, Float{129.13f});
  CHECK_EQ(Float{v1.distance(v2)}, Float{17.5102826933f});

  auto v1_copy = v1;
  v1_copy.normalize();
  CHECK_EQ(v1_copy, vec3{0.147957489f, -0.621421454f, 0.769378943f});
  auto v2_norm = v2.normalized();
  CHECK_EQ(v2_norm, vec3{-0.4400038016f, 0.8184070711f, -0.3696031934f});
  CHECK_EQ(v1.cross(v2), vec3{-30.72000313f, -21.79999924f, -11.69999981f});
  float angle = v1.angle(v2);
  CHECK_EQ(Float{angle}, Float{2.60224223f});
  CHECK_EQ(Float{rad2deg(angle)}, Float{149.097427f});
  CHECK_EQ(Float{deg2rad(rad2deg(angle))}, Float{angle});
  CHECK_EQ(v1.project(v2), vec3{2.55169177f, -4.74614668f, 2.14342093});
  CHECK_EQ(v1.perpendicular(v2), vec3{-1.55169177f, 0.54614687f, 3.05657887f});
  CHECK_EQ(v1.reflect(v2.normalized()),
           vec3{-4.10338354f, 5.29229355f, 0.91315794f});
}

TEST_SUITE_END;

TEST_SUITE_BEGIN("Matrices Test Suite");
TEST_CASE("Matrices 2x2")
{
  std::cout << "Mat 2x2\n" << mat2{} << '\n';
  mat2 m2    = {1.0f, -1.0f, -1.0f, -1.0f};
  mat2 m2_T  = {1.0f, -1.0f, -1.0f, -1.0f};
  mat2 m2_x2 = {2.0f, -2.0f, -2.0f, -2.0f};
  mat2 m2Sq  = {2.0f, 0.0f, 0.0f, 2.0f};
  CHECK_EQ(Float(-1.0f), Float{m2[1][1]});
  CHECK_EQ(Float{-1.0f}, Float{m2._12});
  CHECK_EQ(Float{1.0f}, Float{m2.arr.at(0)});
  CHECK_EQ(m2.transposed(), m2_T);
  m2_T.transpose();
  CHECK_EQ(m2_T, m2);
  CHECK_EQ(m2 * 2.0f, m2_x2);
  CHECK_EQ(m2 * m2, m2Sq);
  CHECK_EQ(m2.determinant(), -2);

  m2 = mat2{1, 3, 8, -2};
  mat2 minor{-2, 8, 3, 1};
  mat2 adj{-2, -3, -8, 1};
  float det = -26.0f;
  CHECK_EQ(m2.minor(), minor);
  CHECK_EQ(m2.determinant(), det);
  CHECK_EQ(m2.adjugate(), adj);
  CHECK_EQ(m2.inverse(), adj * (1.0f / det));
}

TEST_CASE("Matrices 3x3")
{
  std::cout << "Mat 3x3\n" << mat3{} << '\n';
  mat3 m3    = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  mat3 m3_T  = {1.0f, 4.0f, 7.0f, 2.0f, 5.0f, 8.0f, 3.0f, 6.0f, 9.0f};
  mat3 m3_x2 = {2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f};
  mat3 m3Sq  = {30.0f, 36.0f,  42.0f,  66.0f, 81.0f,
                96.0f, 102.0f, 126.0f, 150.0f};

  CHECK_EQ(Float(6.0f), Float{m3[1][2]});
  CHECK_EQ(Float{7.0f}, Float{m3._31});
  CHECK_EQ(Float{9.0f}, Float{m3.arr.at(8)});

  CHECK_EQ(m3.transposed(), m3_T);
  m3_T.transpose();

  CHECK_EQ(m3_T, m3);
  CHECK_EQ(m3_T * 2.0f, m3_x2);
  CHECK_EQ(m3 * m3, m3Sq);
  CHECK_EQ(m3.determinant(), 0.0f);

  m3 = mat3{1, 8, 7, 3, 9, 5, 1, 0, 4};
  mat3 minor{36, 7, -9, 32, -3, -8, -23, -16, -15};
  mat3 adj{36, -32, -23, -7, -3, 16, -9, 8, -15};
  float det   = -83.0f;
  float angle = 1.4f;
  mat3 x_rotation{1.,          0., 0.,           0.,         0.16996716f,
                  0.98544973f, 0., -0.98544973f, 0.16996716f};
  mat3 y_rotation{0.16996716f, 0.,          -0.98544973f, 0.,         1.,
                  0.,          0.98544973f, 0.,           0.16996716f};
  mat3 z_rotation{0.16996716f, 0.98544973f, 0., -0.98544973f, 0.16996716f, 0.,
                  0.,          0.,          1.};
  vec3 euler_angles{0., 0, 3.1415f / 3};
  mat3 rot_matrix{-1., -0., 0., 0., -1., 0., 0., 0., 1.};
  // mat3 rotMatrix {-0.899889, -0.114726, 0.420758,-0.259955, -0.633551,
  // -0.728722, 0.350175, -0.765147, 0.540302};
  CHECK_EQ(m3.minor(), minor);
  CHECK_EQ(m3.determinant(), det);
  CHECK_EQ(m3.adjugate(), adj);
  CHECK_EQ(m3.inverse(), adj * (1.0f / det));
  CHECK_EQ(m3.rotation_matrix({1, 0, 0}, angle), x_rotation);
  CHECK_EQ(m3.rotation_matrix({0, 1, 0}, angle), y_rotation);
  CHECK_EQ(m3.rotation_matrix({0, 0, 1}, angle), z_rotation);
  CHECK_EQ(mat3::rotation_X(angle), x_rotation);
  CHECK_EQ(mat3::rotation_Y(angle), y_rotation);
  CHECK_EQ(mat3::rotation_Z(angle), z_rotation);
  // CHECK_EQ(mat::mat3::rotation_matrix(eulerAngles), rot_matrix);
  CHECK_EQ(isaac::mat3::mult_vector({1.f, 2.f, 3.f}, m3),
           vec3{10.f, 26.f, 29.f});
}

TEST_CASE("Matrices 4x4")
{
  std::cout << "Mat 4x4\n" << mat4{} << '\n';
  mat4 m4    = {1.0f, 2.0f,  3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  8.0f,
                9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  mat4 m4_T  = {1.0f, 5.0f, 9.0f,  13.0f, 2.0f, 6.0f, 10.0f, 14.0f,
                3.0f, 7.0f, 11.0f, 15.0f, 4.0f, 8.0f, 12.0f, 16.0f};
  mat4 m4_x2 = {2.0f,  4.0f,  6.0f,  8.0f,  10.0f, 12.0f, 14.0f, 16.0f,
                18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
  mat4 m4Sq  = {90,  100, 110, 120, 202, 228, 254, 280,
                314, 356, 398, 440, 426, 484, 542, 600};
  CHECK_EQ(Float(15.0f), Float{m4[3][2]});
  CHECK_EQ(Float{8.0f}, Float{m4._24});
  CHECK_EQ(Float{9.0f}, Float{m4.arr.at(8)});
  CHECK_EQ(m4.transposed(), m4_T);
  m4_T.transpose();
  CHECK_EQ(m4_T, m4);
  CHECK_EQ(m4 * 2.0f, m4_x2);
  CHECK_EQ(m4 * m4, m4Sq);

  m4 = mat4{1.0f, -2.0f, 3.0f,  4.0f,  5.0f,  6.0f,  7.0f,  -8.0f,
            9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  mat4 m4_minors{64,    128,  64,  0,   16,   0,    -48, -32,
                 -1120, -384, 544, -64, -816, -256, 400, -32};
  mat4 m4_cof{64,    -128, 64,  0,  -16, 0,    48,   -32,
              -1120, 384,  544, 64, 816, -256, -400, -32};
  mat4 m4_adj{64, -16, -1120, 816,  -128, 0,   384, -256,
              64, 48,  544,   -400, 0,    -32, 64,  -32};
  float det = 512.0f;

  CHECK_EQ(m4.minor(), m4_minors);
  CHECK_EQ(m4.cofactor(), m4_cof);
  CHECK_EQ(m4.determinant(), det);
  CHECK_EQ(m4.adjugate(), m4_adj);
  CHECK_EQ(m4.inverse(), m4_adj * (1.0f / det));

  mat4 trans_matrix = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 3, 4, 5, 1};
  mat4 scale_matrix = {3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 5, 0, 0, 0, 0, 1};
  vec3 vec          = {3, 4, 5};
  CHECK_EQ(mat4::translation(3, 4, 5), trans_matrix);
  CHECK_EQ(mat4::translation(vec), trans_matrix);
  CHECK_EQ(trans_matrix.get_translation(), vec);
  CHECK_EQ(mat4::scale_matrix(3, 4, 5), scale_matrix);
  CHECK_EQ(mat4::scale_matrix(vec), scale_matrix);
  CHECK_EQ(scale_matrix.get_scale(), vec);
}

TEST_SUITE_END;

TEST_SUITE_BEGIN("Geometry2D Intersections Test Suite");

TEST_CASE("Line Intersections")
{
  isaac::Line2D line{{7, -2}, {-8, 3}};
  CHECK_EQ(line.bounds(), Rectangle2D{{-8.0f, -2.0f}, {15, 5}});
  CHECK(isaac::point_on_line({4, -1}, line));
  CHECK(isaac::point_on_line({10, -3}, line));
  CHECK_FALSE(isaac::point_on_line({5, -1}, line));

  CHECK(line.intersects(Circle2D{{-1, 0.6}, 1}));
  CHECK(line.intersects(Circle2D{{1.5, -0.5}, 0.5}));
  CHECK_FALSE(line.intersects(Circle2D{{2, 1}, 0.5}));
  CHECK(line.intersects(Rectangle2D{{2.2, -0.5}, {3, 3}}));
  CHECK(line.intersects(Rectangle2D{{-3.3, 1.1}, {2, 1}}));
  CHECK_FALSE(line.intersects(Rectangle2D{{-2, 1.5}, {2, 1}}));
  CHECK(line.intersects(OrientedRectangle2D{{2.2, -0.5}, {3, 3}}));
  CHECK(line.intersects(OrientedRectangle2D{{0, 0.5}, {0.8, 0.1}}));
  CHECK_FALSE(
      line.intersects(OrientedRectangle2D{{0, 0.5}, {0.8, 0.1}, deg2rad(-18)}));
}

TEST_CASE("Circle2D Intersections")
{
  isaac::Circle2D circle{{-5, 2}, 2.5};
  CHECK_EQ(circle.bounds(), Rectangle2D{{-7.5f, -0.5f}, {5, 5}});
  CHECK(isaac::point_in_circle({-6, 1.3}, circle));
  CHECK(isaac::point_in_circle({-4, 0.8}, circle));
  CHECK(isaac::point_in_circle({-5.5, 1}, circle));
  CHECK_FALSE(isaac::point_in_circle({5.5, 1}, circle));
  CHECK_FALSE(isaac::point_in_circle({5.5, 1}, circle));
  CHECK_FALSE(isaac::point_in_circle({-5.5, -1}, circle));

  CHECK(circle.intersects(Line2D{{7, -2}, {-8, 3}}));
  CHECK_FALSE(circle.intersects(Line2D{{-7, -2}, {-8, 3}}));
  CHECK(circle.intersects(Circle2D{{-2, 3}, 1}));
  CHECK(circle.intersects(Circle2D{{2, -3}, 6.5}));
  CHECK_FALSE(circle.intersects(Circle2D{{-2, 3}, 0.4}));
  CHECK_FALSE(circle.intersects(Circle2D{{2, -3}, 2}));

  CHECK(circle.intersects(Rectangle2D{{-6, -3}, {4, 2.5}}));
  CHECK_FALSE(circle.intersects(Rectangle2D{{-6, -3}, {4, 2.4}}));
  CHECK(circle.intersects(Rectangle2D{{-3, 3}, {1, 1}}));
  CHECK_FALSE(circle.intersects(Rectangle2D{{-2.5, 3}, {1, 1}}));

  CHECK(circle.intersects(OrientedRectangle2D{{-6, -3}, {4, 2.4}, 45}));
  CHECK_FALSE(circle.intersects(OrientedRectangle2D{{-6, -3}, {4, 2.4}}));
  CHECK(
      circle.intersects(OrientedRectangle2D{{-6, 6}, {10, 0.5}, deg2rad(-45)}));
  CHECK_FALSE(circle.intersects(OrientedRectangle2D{{-6, 6}, {10, 0.5}}));
}

TEST_CASE("Rectangle2D Intersections")
{
  Rectangle2D rect{{1, 2}, {4, 5}};
  CHECK_EQ(rect.bounds(), rect);
  CHECK(isaac::point_in_rectangle({3.5, 3.5}, rect));
  CHECK(isaac::point_in_rectangle({1.1, 6.9}, rect));
  CHECK(isaac::point_in_rectangle({4.9, 2.1}, rect));
  CHECK_FALSE(isaac::point_in_rectangle({5.2, 2.1}, rect));
  CHECK_FALSE(isaac::point_in_rectangle({3, 0.9}, rect));
  CHECK(rect.intersects(Line2D{{-5, -5}, {5, 10}}));
  CHECK_FALSE(rect.intersects(Line2D{{7, -2}, {-8, 3}}));
  CHECK(rect.intersects(Circle2D{{-2, -2}, 5.0}));
  CHECK(rect.intersects(Circle2D{{-2, -2}, 5.1}));
  CHECK_FALSE(rect.intersects(Circle2D{{-2, -2}, 4.9}));
  CHECK(rect.intersects(Rectangle2D{{-5, -2.5}, {6.5, 5.5}}));
  CHECK_FALSE(rect.intersects(Rectangle2D{{-5, -2.5}, {6.5, 4}}));
  CHECK(rect.intersects_SAT(Rectangle2D{{-5, -2.5}, {6.5, 5.5}}));
  CHECK_FALSE(rect.intersects_SAT(Rectangle2D{{-5, -2.5}, {6.5, 4}}));
  CHECK_FALSE(rect.intersects(OrientedRectangle2D{{0, 0}, {3, 1}}));
  CHECK_FALSE(
      rect.intersects(OrientedRectangle2D{{0, 0}, {3, 1}, deg2rad(15)}));
  CHECK(rect.intersects(OrientedRectangle2D{{0, 0}, {3, 1}, deg2rad(25)}));
  CHECK(rect.intersects(OrientedRectangle2D{{-1, 2}, {3, 1}}));
  CHECK(rect.intersects(OrientedRectangle2D{{-1, 2}, {3, 1}, deg2rad(15)}));
  CHECK_FALSE(
      rect.intersects(OrientedRectangle2D{{-1, 2}, {3, 1}, deg2rad(75)}));
}

TEST_CASE("OrientedRectangle2D Intersections")
{
  OrientedRectangle2D oriented_rect{{1, 2}, {3, 1}, deg2rad(30)};
  CHECK_EQ(oriented_rect.bounds(), Rectangle2D{{-2.09807611f, -0.366025925f},
                                               {6.19615173f, 4.73205185f}});
  CHECK(point_in_oriented_rectangle({3, 4}, oriented_rect));
  CHECK(oriented_rect.intersects(Line2D{{2, -1}, {-1, 4}}));
  CHECK_FALSE(oriented_rect.intersects(Line2D{{2, -1}, {5, 3}}));
  CHECK(oriented_rect.intersects({{3, 1}, 1}));
  CHECK_FALSE(oriented_rect.intersects({{3, 0}, 1}));
  CHECK(oriented_rect.intersects({{-1, 3}, 1}));
  CHECK_FALSE(oriented_rect.intersects({{-1, 3}, 0.5}));
  CHECK(oriented_rect.intersects(Rectangle2D{{-3, 2}, {3, 1.5}}));
  CHECK_FALSE(oriented_rect.intersects(Rectangle2D{{1, -1}, {3, 1.5}}));
  CHECK(oriented_rect.intersects(OrientedRectangle2D{{0, 4}, {1.5, 0.75}}));
  CHECK(oriented_rect.intersects(
      OrientedRectangle2D{{5, 3}, {1.5, 0.75}, deg2rad(-15)}));
  CHECK(oriented_rect.intersects(
      OrientedRectangle2D{{5, 3}, {1.5, 0.75}, deg2rad(10)}));
  CHECK_FALSE(oriented_rect.intersects(
      OrientedRectangle2D{{5, 3}, {1.5, 0.75}, deg2rad(76)}));
}

TEST_CASE("BoundingShapes2D Intersections")
{
  BoundingShape2D bs{};

  CHECK(!bs.has_area());

  bs.add_shape(Circle2D{{-5, 2}, 2.5});
  bs.add_shape(Rectangle2D{{1, 2}, {4, 5}});
  bs.add_shape(OrientedRectangle2D{{-1, -1}, {2, 3}, deg2rad(30)});

  CHECK(bs.has_area());

  CHECK(isaac::point_in_bounding_shape({3.5, 3.5}, bs));
  CHECK(isaac::point_in_bounding_shape({1.1, 6.9}, bs));
  CHECK(isaac::point_in_bounding_shape({4.9, 2.1}, bs));
  CHECK_FALSE(isaac::point_in_bounding_shape({5.2, 2.1}, bs));
  CHECK_FALSE(isaac::point_in_bounding_shape({3, 0.9}, bs));
  CHECK(isaac::point_in_bounding_shape({-6, 1.3}, bs));
  CHECK(isaac::point_in_bounding_shape({-4, 0.8}, bs));
  CHECK(isaac::point_in_bounding_shape({-5.5, 1}, bs));
  CHECK_FALSE(isaac::point_in_bounding_shape({5.5, 1}, bs));
  CHECK_FALSE(isaac::point_in_bounding_shape({5.5, 1}, bs));
  CHECK_FALSE(isaac::point_in_bounding_shape({-5.5, -1}, bs));

  CHECK(bs.intersects(Circle2D{{0, 0}, 1}));
  CHECK(bs.intersects(Circle2D{{5, 1.5}, 1}));
  CHECK(!bs.intersects(Circle2D{{5, 0.5}, 1}));
  CHECK(!bs.intersects(Rectangle2D{{1, 0.5}, {3, 1}}));
  CHECK(bs.intersects(Rectangle2D{{0.2, 0.5}, {3, 1}}));
  CHECK(bs.intersects(OrientedRectangle2D{{4.8, -1}, {3, 1}, deg2rad(15)}));
  CHECK(!bs.intersects(OrientedRectangle2D{{4.8, -1}, {3, 1}, deg2rad(-15)}));

  Rectangle2D const bounds{{-7.5, -4.59807634}, {12.5, 11.5980759}};
  CHECK_EQ(bs.bounds(), bounds);
  bs.set_position({1, 0});
  auto shapes = bs.get_shapes();
  auto c      = std::get<Circle2D>(shapes[0]);
  auto r      = std::get<Rectangle2D>(shapes[1]);
  auto rr     = std::get<OrientedRectangle2D>(shapes[2]);
  CHECK_EQ(c.position, vec2{-2.75, 0.79903841});
  CHECK_EQ(r.origin, vec2{3.25, 0.79903841});
  CHECK_EQ(rr.position, vec2{1.25, -2.20096159});
}

TEST_CASE("Containing Shapes")
{
  std::vector<Point2D> const shape{
      {2, 2}, {2, -2}, {-2, -4}, {-1, -1}, {-2, 1}};
  Circle2D circle{containing_circle(shape)};
  CHECK_EQ(circle.position, vec2{-0.2, -0.8});
  CHECK_EQ(Float{circle.radius}, Float{3.671512});

  Rectangle2D rect{containing_rectangle(shape)};
  CHECK_EQ(rect.origin, vec2{-2, -4});
  CHECK_EQ(rect.size, vec2{4, 6});
}

TEST_CASE("QuadTree")
{
  Rectangle2D const canvas{Point2D{-10, -10}, {20, 20}};
  QuadTree<Shape2D, 15, 4> qt{canvas};
  CHECK_EQ(qt.num_objects(), 0);
  CHECK_EQ(qt.query(canvas).size(), 0);
  CHECK(qt.is_leaf());

  // clang-format off
  std::vector<Shape2D> shapes{
    Circle2D{{0, 0}, 2},
    Rectangle2D{{-4, 3}, {2, 1}},
    OrientedRectangle2D{{3, 4}, {3, 2}, deg2rad(30)},
    Circle2D{{-6, -7}, 1}
  };

  auto make_qt_data = [](auto &shape) {
    auto bounds = std::visit([](auto &s) { return s.bounds(); }, shape);
    return QuadTreeData<Shape2D>{&shape, bounds};
  };
  // clang-format on

  // Insert data points
  for (auto&& shape : shapes) {
    qt.insert(make_qt_data(shape));
  }

  CHECK_EQ(qt.num_objects(), shapes.size());
  CHECK_EQ(qt.query(canvas).size(), shapes.size());
  CHECK(qt.is_leaf());
  {
    // Test delete
    auto& shape = shapes.back();
    auto& f     = std::get<Circle2D>(shape);
    QuadTreeData<Shape2D> to_update{&shape, f.bounds()};
    CHECK_EQ(qt.num_objects(), shapes.size());
    qt.remove(to_update);
    CHECK_EQ(qt.num_objects(), shapes.size() - 1);
    qt.insert(to_update);
    CHECK_EQ(qt.num_objects(), shapes.size());
  }
  {
    // Test query single object
    auto res = qt.query({{-8, -8}, {1, 1}});
    CHECK_EQ(res.size(), 1);
    auto& shape = shapes.back();
    auto& found = *res.front()->object;
    CHECK_EQ(&shape, &found);

    auto& f = std::get<Circle2D>(shape);
    auto& r = std::get<Circle2D>(found);
    CHECK_EQ(f.position, r.position);
    CHECK_EQ(Float{f.radius}, Float{r.radius});
    CHECK_EQ(&f, &r);
  }
  {
    // Test update
    auto res = qt.query({{-8, -8}, {1, 1}});
    CHECK_EQ(res.size(), 1);
    auto& shape = shapes.back();
    auto& found = *res.front()->object;
    CHECK_EQ(&shape, &found);
    auto& circle    = std::get<Circle2D>(shape);
    circle.position = Point2D{6, -7};
    assert(std::get<Circle2D>(shape).position == circle.position);
    QuadTreeData<Shape2D> to_update{&shape, circle.bounds()};
    qt.update(to_update);
    CHECK_EQ(qt.num_objects(), shapes.size());
    res = qt.query({{-8, -8}, {1, 1}});
    CHECK_EQ(res.size(), 0);
    res = qt.query({{5.5, -8}, {1, 1}});
    CHECK_EQ(res.size(), 1);
    auto& r = std::get<Circle2D>(*res.front()->object);
    CHECK_EQ(&circle, &r);
  }
  {
    // Test query multiple objects
    auto res = qt.query({{1, 1}, {1, 1}});
    CHECK_EQ(res.size(), 2);
    auto& a = std::get<Circle2D>(shapes.at(0));
    auto& b = std::get<OrientedRectangle2D>(shapes.at(2));
    for (auto&& r_data : res) {
      auto r = r_data->object;
      if (Circle2D* p_circ = std::get_if<Circle2D>(r)) {
        CHECK_EQ(p_circ->position, a.position);
        CHECK_EQ(Float{p_circ->radius}, Float{a.radius});
        CHECK_EQ(p_circ, &a);
      } else if (OrientedRectangle2D* p_rect =
                     std::get_if<OrientedRectangle2D>(r)) {
        CHECK_EQ(p_rect->position, b.position);
        CHECK_EQ(p_rect->half_extents, b.half_extents);
        CHECK_EQ(Float{p_rect->rotation}, Float{b.rotation});
        CHECK_EQ(p_rect, &b);
      } else {
        throw std::domain_error("Wrong shape");
      }
    }
  }

  shapes.push_back(Circle2D{{3, 4}, 1});
  shapes.push_back(OrientedRectangle2D{{4, 5}, {2.5, 1}, deg2rad(-45)});
  shapes.push_back(Circle2D{{5, 4.5}, 2});

  // Split!
  for (auto it = shapes.end() - 3; it != shapes.end(); ++it) {
    qt.insert(make_qt_data(*it));
  }
  CHECK_EQ(qt.num_objects(), shapes.size());
  CHECK_EQ(qt.query(canvas).size(), shapes.size());
}

TEST_SUITE_END;