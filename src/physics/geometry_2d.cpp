#include "physics/geometry_2d.hpp"
#include "physics/math.hpp"

#include <algorithm>
#include <vector>

namespace isaac {

bool point_on_line(Point2D const& point, Line2D const& line)
{
  // Find the slope
  vec2 diff = line.end - line.start;
  float m   = diff.y / diff.x;
  float b   = line.start.y - m * line.start.x;
  return cmp(point.y, m * point.x + b);
}

bool point_in_circle(Point2D const& point, Circle2D const& circle)
{
  Line2D line{point, circle.position};
  return line.length_sq() < circle.radius * circle.radius;
}

bool point_in_rectangle(Point2D const& point, Rectangle2D const& rectangle)
{
  vec2 min = rectangle.get_min();
  vec2 max = rectangle.get_max();
  return min.x <= point.x && min.y <= point.y && point.x <= max.x
      && point.y <= max.y;
}

bool point_in_oriented_rectangle(Point2D const& point,
                              OrientedRectangle2D const& rectangle)
{
  vec2 rot_vector = point - rectangle.position;
  float theta    = -rectangle.rotation;
  mat2 z_rotation_2x2{std::cos(theta), std ::sin(theta), -std::sin(theta),
                    std::cos(theta)};
  rot_vector = mult(rot_vector, z_rotation_2x2);
  Rectangle2D local_rectangle{Point2D{}, rectangle.half_extents * 2.0f};
  vec2 local_point = rot_vector + rectangle.half_extents;
  return point_in_rectangle(local_point, local_rectangle);
}

// Helper structs for visitor
template<class... Ts>
struct overloaded : Ts...
{
  using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

bool point_in_bounding_shape(Point2D const& point,
                          BoundingShape2D const& bounding_shape)
{
  auto intersects = [&](Shape2D const& s) {
    return std::visit(overloaded{[&](Circle2D const& circle) {
                                   return point_in_circle(point, circle);
                                 },
                                 [&](Rectangle2D const& rectangle) {
                                   return point_in_rectangle(point, rectangle);
                                 },
                                 [&](OrientedRectangle2D const& rectangle) {
                                   return point_in_oriented_rectangle(point,
                                                                   rectangle);
                                 }},
                      s);
  };

  auto& shapes = bounding_shape.get_shapes();
  return std::any_of(shapes.begin(), shapes.end(), intersects);
}
bool BoundingShape2D::has_area() const
{
  return !m_shapes.empty();
}

auto z_rotation = [](vec2 const& v, float angle) {
  mat2 z_rot = {std::cos(angle), std::sin(angle), -std::sin(angle),
                std::cos(angle)};
  return mult(v, z_rot);
};

// ---------------------
// Line2D

Rectangle2D Line2D::bounds() const
{
  return containing_rectangle({start, end});
}

float Line2D::length() const
{
  return (start - end).magnitude();
}

float Line2D::length_sq() const
{
  return (start - end).magnitude_sq();
}

bool Line2D::intersects(Circle2D const& circle) const
{
  vec2 ab = end - start;
  float t = (circle.position - start).dot(ab) / ab.dot(ab);
  if (t < 0.0f || t > 1)
    return false;
  Point2D closest = start + ab * t;
  Line2D distance{circle.position, closest};
  return distance.length_sq() < circle.radius * circle.radius;
}

bool Line2D::intersects(Rectangle2D const& rectangle) const
{
  if (point_in_rectangle(start, rectangle) || point_in_rectangle(end, rectangle))
    return true;
  vec2 norm = (end - start).normalized();
  norm.x    = (norm.x != 0) ? 1.0f / norm.x : 0;
  norm.y    = (norm.y != 0) ? 1.0f / norm.y : 0;

  vec2 min = (rectangle.get_min() - start) * norm;
  vec2 max = (rectangle.get_max() - start) * norm;

  float tmin = std::max(std::min(min.x, max.x), std::min(min.y, max.y));
  float tmax = std::min(std::max(min.x, max.x), std::max(min.y, max.y));

  if (tmax < 0 || tmin > tmax)
    return false;

  float t = (tmin < 0) ? tmax : tmin;
  return t > 0 && (t * t) < length_sq();
}

bool Line2D::intersects(OrientedRectangle2D const& rectangle) const
{
  float const theta = -rectangle.rotation;
  Line2D local_line;
  vec2 rot_vector  = z_rotation(start - rectangle.position, theta);
  local_line.start = rot_vector + rectangle.half_extents;

  rot_vector     = z_rotation(end - rectangle.position, theta);
  local_line.end = rot_vector + rectangle.half_extents;

  Rectangle2D local_rectangle{{}, rectangle.half_extents * 2};
  return local_line.intersects(local_rectangle);
}

// ---------------------
// Circle2D

Rectangle2D Circle2D::bounds() const
{
  vec2 origin{position - vec2{radius, radius}};
  vec2 size{2 * radius, 2 * radius};
  return {origin, size};
}

bool Circle2D::intersects(Line2D const& line) const
{
  return line.intersects(*this);
}

bool Circle2D::intersects(Circle2D const& circle) const
{
  Line2D distance{position, circle.position};
  float radii_sum = radius + circle.radius;
  return distance.length_sq() <= radii_sum * radii_sum;
}

bool Circle2D::intersects(Rectangle2D const& rectangle) const
{
  vec2 const min       = rectangle.get_min();
  vec2 const max       = rectangle.get_max();
  Point2D closest_point = position;
  closest_point.x       = clamp(closest_point.x, min.x, max.x);
  closest_point.y       = clamp(closest_point.y, min.y, max.y);
  Line2D line{position, closest_point};
  return line.length_sq() <= radius * radius;
}

bool Circle2D::intersects(OrientedRectangle2D const& rectangle) const
{
  vec2 r      = position - rectangle.position;
  float theta = -rectangle.rotation;
  r           = z_rotation(r, theta);
  Circle2D local_circle{r + rectangle.half_extents, radius};
  Rectangle2D local_rectangle{{}, rectangle.half_extents * 2.0f};
  return local_circle.intersects(local_rectangle);
}

// ---------------------
// Rectangle2D

Rectangle2D Rectangle2D::bounds() const
{
  return *this;
}

vec2 Rectangle2D::get_min() const
{
  auto p1 = origin;
  auto p2 = origin + size;
  return vec2{std::min(p1.x, p2.x), std::min(p1.y, p2.y)};
}

vec2 Rectangle2D::get_max() const
{
  auto p1 = origin;
  auto p2 = origin + size;
  return vec2{std::max(p1.x, p2.x), std::max(p1.y, p2.y)};
}

Interval2D Rectangle2D::get_interval(vec2 const& axis) const
{
  vec2 const min = get_min();
  vec2 const max = get_max();
  std::array<vec2, 4> const vertices{vec2{min.x, min.y}, vec2{min.x, max.y},
                                     vec2{max.x, max.y}, vec2{max.x, min.y}};
  Interval2D result{};
  result.min = result.max = axis.dot(vertices[0]);
  for (auto& v : vertices) {
    float projection = axis.dot(v);
    if (projection < result.min)
      result.min = projection;
    if (projection > result.max)
      result.max = projection;
  }
  return result;
}

Rectangle2D Rectangle2D::from_min_max(vec2 const& min, vec2 const& max)
{
  return {min, max - min};
}

bool Rectangle2D::intersects(Line2D const& line) const
{
  return line.intersects(*this);
}
bool Rectangle2D::intersects(Circle2D const& circle) const
{
  return circle.intersects(*this);
}
bool Rectangle2D::intersects(Rectangle2D const& rectangle) const
{
  vec2 const a_min = get_min();
  vec2 const a_max = get_max();
  vec2 const b_min = rectangle.get_min();
  vec2 const b_max = rectangle.get_max();
  bool over_X      = ((b_min.x <= a_max.x) && (a_min.x <= b_max.x));
  bool over_Y      = ((b_min.y <= a_max.y) && (a_min.y <= b_max.y));
  return over_X && over_Y;
}

bool Rectangle2D::intersects(OrientedRectangle2D const& rectangle) const
{
  std::array<vec2, 4> axis_to_test{{{1, 0}, {0, 1}, {}, {}}};
  float theta = rectangle.rotation;
  vec2 axis{rectangle.half_extents.x, 0};
  axis.normalize();
  axis_to_test[2] = z_rotation(axis, theta);
  axis          = vec2{0, rectangle.half_extents.y};
  axis.normalize();
  axis_to_test[3] = z_rotation(axis, theta);
  return std::all_of(axis_to_test.begin(), axis_to_test.end(), [&](vec2 const& ax) {
    return rectangle.overlap_on_axis(*this, ax);
  });
}

/// Return true if an overlap exists
bool Rectangle2D::overlap_on_axis(Rectangle2D const& rectangle,
                                vec2 const& axis) const
{
  Interval2D a = this->get_interval(axis);
  Interval2D b = rectangle.get_interval(axis);
  return ((b.min <= a.max) && (a.min <= b.max));
}

bool Rectangle2D::intersects_SAT(Rectangle2D const& rectangle) const
{
  std::array<vec2, 2> axis_to_test{vec2{1, 0}, vec2{0, 1}};
  return std::all_of(
      axis_to_test.begin(), axis_to_test.end(),
      [&](vec2 const& axis) { return this->overlap_on_axis(rectangle, axis); });
}

bool operator==(Rectangle2D const& r1, Rectangle2D const& r2)
{
  return r1.origin == r2.origin && r1.size == r2.size;
}

// ---------------------
// OrientedRectangle2D

Rectangle2D OrientedRectangle2D::bounds() const
{
  Rectangle2D rect{position - half_extents, half_extents * 2.0f};
  vec2 min = rect.get_min();
  vec2 max = rect.get_max();
  std::vector<Point2D> vertices{min, max, vec2{min.x, max.y},
                                vec2{max.x, min.y}};
  float theta = rotation;
  std::for_each(vertices.begin(), vertices.end(), [&](auto& v) {
    v -= position;
    v = z_rotation(v, theta);
    v += position;
  });
  return containing_rectangle(vertices);
}

Interval2D OrientedRectangle2D::get_interval(vec2 const& axis) const
{
  Rectangle2D rect{position - half_extents, half_extents * 2.0f};
  vec2 min = rect.get_min();
  vec2 max = rect.get_max();
  std::vector<vec2> vertices{min, max, vec2{min.x, max.y}, vec2{max.x, min.y}};
  float theta = rotation;
  std::for_each(vertices.begin(), vertices.end(), [&](auto& v) {
    v -= position;
    v = z_rotation(v, theta);
    v += position;
  });

  Interval2D res{};
  res.min = res.max = axis.dot(vertices[0]);
  std::for_each(vertices.begin(), vertices.end(), [&](auto const& v) {
    float proj = axis.dot(v);
    res.min    = std::min(proj, res.min);
    res.max    = std::max(proj, res.max);
  });
  return res;
}

bool OrientedRectangle2D::intersects(Line2D const& line) const
{
  return line.intersects(*this);
}
bool OrientedRectangle2D::intersects(Circle2D const& circle) const
{
  return circle.intersects(*this);
}
bool OrientedRectangle2D::intersects(Rectangle2D const& rectangle) const
{
  return rectangle.intersects(*this);
}
bool OrientedRectangle2D::intersects(OrientedRectangle2D const& rectangle) const
{
  Rectangle2D local_rect_1{Point2D{}, half_extents * 2.0f};
  vec2 r = rectangle.position - position;
  OrientedRectangle2D local_rect_2{rectangle.position, rectangle.half_extents,
                                 rectangle.rotation};
  local_rect_2.rotation = rectangle.rotation - rotation;
  float theta         = -rotation;
  r                   = z_rotation(r, theta);
  local_rect_2.position = r + half_extents;
  return local_rect_1.intersects(local_rect_2);
}
bool OrientedRectangle2D::overlap_on_axis(Rectangle2D const& rectangle2D,
                                        vec2 const& axis) const
{
  Interval2D a{rectangle2D.get_interval(axis)};
  Interval2D b{get_interval(axis)};
  return (b.min <= a.max) && (a.min <= b.max);
}

// Container shapes
Circle2D containing_circle(std::vector<Point2D> const& points)
{
  Point2D center;
  std::for_each(points.begin(), points.end(),
                [&center](auto const& p) { center += p; });

  center /= static_cast<float>(points.size());
  Circle2D result{center, 1.0f};
  result.radius = vec::magnitude_sq(center - points[0]);

  std::for_each(points.begin() + 1, points.end(),
                [&center, &result](auto const& p) {
                  float distance = vec::magnitude_sq(center - p);
                  if (distance > result.radius)
                    result.radius = distance;
                });
  result.radius = std::sqrt(result.radius);
  return result;
}

Rectangle2D containing_rectangle(std::vector<Point2D> const& points)
{
  auto min = points[0];
  auto max = points[0];
  std::for_each(points.begin() + 1, points.end(), [&min, &max](auto const& p) {
    min.x = std::min(p.x, min.x);
    min.y = std::min(p.y, min.y);
    max.x = std::max(p.x, max.x);
    max.y = std::max(p.y, max.y);
  });
  return Rectangle2D::from_min_max(min, max);
}

void BoundingShape2D::add_shape(Shape2D shape)
{
  m_shapes.emplace_back(std::move(shape));
}

std::vector<Shape2D> const& BoundingShape2D::get_shapes() const
{
  return m_shapes;
}

bool BoundingShape2D::intersects(Shape2D const& shape) const
{
  // clang-format off
  auto intersects = [&shape](Shape2D const& current_shape) {
    return std::visit([&current_shape](const auto& other) {
      return std::visit([&other](const auto &current) {
        return current.intersects(other);
      }, current_shape);
    }, shape);
  };
  // clang-format on
  return std::any_of(m_shapes.begin(), m_shapes.end(), intersects);
}
vec2 BoundingShape2D::get_position() const
{
  auto const b = bounds();
  return {b.origin.x + b.size.x / 2, b.origin.y + b.size.y / 2};
}

void BoundingShape2D::set_position(vec2 const& position)
{
  auto displacement = position - get_position();
  // clang-format off
  for (auto &&shape : m_shapes) {
    std::visit(overloaded {
        [&displacement](Circle2D &c) { c.position += displacement; },
        [&displacement](Rectangle2D &r) { r.origin += displacement; },
        [&displacement](OrientedRectangle2D &r) { r.position += displacement; },
    }, shape);
  }
  // clang-format on
}

Rectangle2D BoundingShape2D::bounds() const
{
  auto get_bounds = [](Shape2D const& shape) {
    return std::visit([](auto const& s) { return s.bounds(); }, shape);
  };

  vec2 min{0, 0};
  vec2 max{0, 0};

  for (auto&& s : m_shapes) {
    auto const bounds     = get_bounds(s);
    auto const current_min = bounds.get_min();
    auto const current_max = bounds.get_max();
    min.x                 = std::min(current_min.x, min.x);
    min.y                 = std::min(current_min.y, min.y);
    max.x                 = std::max(current_max.x, max.x);
    max.y                 = std::max(current_max.y, max.y);
  }
  return Rectangle2D::from_min_max(min, max);
}
} // namespace isaac
