#ifndef PHYSICS_GEOMETRY_2D_HPP
#define PHYSICS_GEOMETRY_2D_HPP

#include "matrix.hpp"
#include "vector.hpp"

#include <variant>
#include <vector>

namespace isaac {

using Point2D = vec2;
struct Line2D;
struct Circle2D;
struct Rectangle2D;
struct OrientedRectangle2D;
struct BoundingShape2D;
using Shape2D = std::variant<Circle2D, Rectangle2D, OrientedRectangle2D>;

struct Interval2D
{
  float min;
  float max;
};

bool point_on_line(Point2D const& point, Line2D const& line);
bool point_in_circle(Point2D const& point, Circle2D const& circle);
bool point_in_rectangle(Point2D const& point, Rectangle2D const& rectangle);
bool point_in_oriented_rectangle(Point2D const& point,
                                 OrientedRectangle2D const& rectangle);
bool point_in_bounding_shape(Point2D const& point,
                             BoundingShape2D const& bounding_shape);

// ---------------------
// Line2D

struct Line2D
{
  Point2D start;
  Point2D end;
  Line2D() = default;
  Line2D(Point2D const& start, Point2D const& end)
      : start(start)
      , end(end)
  {}
  [[nodiscard]] Rectangle2D bounds() const;
  [[nodiscard]] float length() const;
  [[nodiscard]] float length_sq() const;
  [[nodiscard]] bool intersects(Circle2D const& circle) const;
  [[nodiscard]] bool intersects(Rectangle2D const& rectangle) const;
  [[nodiscard]] bool intersects(OrientedRectangle2D const& rectangle) const;
};

// ---------------------
// Circle2D

struct Circle2D
{
  Point2D position{0.0f, 0.0f};
  float radius{1.0f};
  Circle2D() = default;
  Circle2D(Point2D const& position, float r)
      : position(position)
      , radius(r) {};
  [[nodiscard]] Rectangle2D bounds() const;
  [[nodiscard]] bool intersects(Line2D const& line) const;
  [[nodiscard]] bool intersects(Circle2D const& circle) const;
  [[nodiscard]] bool intersects(Rectangle2D const& rectangle) const;
  [[nodiscard]] bool intersects(OrientedRectangle2D const& rectangle) const;
};

// ---------------------
// Rectangle2D

struct Rectangle2D
{
  Point2D origin{0.f, 0.f};
  vec2 size{1.f, 1.f};
  Rectangle2D() = default;
  Rectangle2D(Point2D const& orig, vec2 const& size)
      : origin(orig)
      , size(size) {};
  [[nodiscard]] Rectangle2D bounds() const;
  [[nodiscard]] vec2 get_min() const;
  [[nodiscard]] vec2 get_max() const;
  [[nodiscard]] Interval2D get_interval(vec2 const& axis) const;
  [[nodiscard]] static Rectangle2D from_min_max(vec2 const& min,
                                                vec2 const& max);
  [[nodiscard]] bool intersects(Line2D const& line) const;
  [[nodiscard]] bool intersects(Circle2D const& circle) const;
  [[nodiscard]] bool intersects(Rectangle2D const& rectangle) const;
  [[nodiscard]] bool intersects(OrientedRectangle2D const& rectangle) const;
  [[nodiscard]] bool intersects_SAT(Rectangle2D const& rectangle) const;
  [[nodiscard]] bool overlap_on_axis(Rectangle2D const& rectangle_2D,
                                     vec2 const& axis) const;
};

bool operator==(Rectangle2D const& r1, Rectangle2D const& r2);

// ---------------------
// OrientedRectangle2D

struct OrientedRectangle2D
{
  Point2D position{0, 0};
  vec2 half_extents{1, 1};
  float rotation{};
  OrientedRectangle2D() = default;
  explicit OrientedRectangle2D(Point2D const& pos, vec2 const& half_exts)
      : position(pos)
      , half_extents(half_exts)
      , rotation{0} {};
  OrientedRectangle2D(Point2D const& pos, vec2 const& half_exts, float angle)
      : position(pos)
      , half_extents(half_exts)
      , rotation{angle} {};
  [[nodiscard]] Rectangle2D bounds() const;
  [[nodiscard]] Interval2D get_interval(vec2 const& axis) const;
  [[nodiscard]] bool intersects(Line2D const& line) const;
  [[nodiscard]] bool intersects(Circle2D const& circle) const;
  [[nodiscard]] bool intersects(Rectangle2D const& rectangle) const;
  [[nodiscard]] bool intersects(OrientedRectangle2D const& rectangle) const;
  [[nodiscard]] bool overlap_on_axis(Rectangle2D const& rectangle2D,
                                     vec2 const& axis) const;
};

struct BoundingShape2D
{
 private:
  std::vector<Shape2D> m_shapes;

 public:
  BoundingShape2D() = default;
  void add_shape(Shape2D shape);
  [[nodiscard]] std::vector<Shape2D> const& get_shapes() const;
  [[nodiscard]] bool intersects(Shape2D const& shape) const;
  [[nodiscard]] bool has_area() const;
  [[nodiscard]] Rectangle2D bounds() const;
  [[nodiscard]] vec2 get_position() const;
  void set_position(vec2 const& position);
};

Circle2D containing_circle(std::vector<Point2D> const& points);
Rectangle2D containing_rectangle(std::vector<Point2D> const& points);
} // namespace issac
#endif
