#ifndef PHYSICS_QUAD_TREE_HPP
#define PHYSICS_QUAD_TREE_HPP

#include "geometry_2d.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

namespace isaac {

template<typename T>
struct QuadTreeData
{
  T* object;
  Rectangle2D bounds;
  bool flag{false};
};

template<typename T, int, int>
class QuadTreeNode
{
  std::vector<QuadTreeNode> m_children;
  std::vector<QuadTreeData<T>> m_contents;
  int m_current_depth;
  Rectangle2D m_node_bounds;

 public:
  explicit QuadTreeNode(Rectangle2D bounds, int depth = 0)
      : m_node_bounds{std::move(bounds)}
      , m_current_depth{depth}
  {
    m_children.reserve(4);
  }
  bool is_leaf();
  [[nodiscard]] int num_objects();
  [[nodiscard]] int current_depth() const;
  bool insert(QuadTreeData<T> data);
  void remove(QuadTreeData<T> const& data);
  void update(QuadTreeData<T> const& data);
  void shake();
  void reset();
  std::vector<QuadTreeData<T>*> query(Rectangle2D const& area);

 private:
  void split();
};

template<typename T, int MaxDept, int MaxObjectsPerNode>
bool QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::is_leaf()
{
  return m_children.empty();
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
int QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::num_objects()
{
  reset();
  int object_count = m_contents.size();
  for (auto&& content : m_contents) {
    content.flag = true;
  }

  using Node = QuadTreeNode<T, MaxDept, MaxObjectsPerNode>;
  std::queue<Node*> to_process{};
  to_process.push(this);

  while (!to_process.empty()) {
    if (auto processing = to_process.front(); !processing->is_leaf()) {
      for (auto&& child : processing->m_children) {
        to_process.push(&child);
      }
    } else {
      for (auto&& content : processing->m_contents) {
        if (!content.flag) {
          object_count++;
          content.flag = true;
        }
      }
    }
    to_process.pop();
  }
  reset();
  return object_count;
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
int QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::current_depth() const
{
  return m_current_depth;
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
bool QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::insert(QuadTreeData<T> data)
{
  if (!data.bounds.intersects(m_node_bounds)) {
    return false; // The object does not fit into this node
  }

  // If there is space in this quad tree and if it doesn't have subdivisions,
  // add the object here
  if (m_contents.size() < MaxObjectsPerNode) {
    m_contents.push_back(std::move(data));
    return true;
  }

  // Otherwise, subdivide and then add the point to whichever node will accept
  // it
  if (is_leaf()) {
    split();
  }

  for (auto&& child : m_children) {
    if (child.insert(std::move(data))) {
      return true;
    }
  }

  // Otherwise, the point cannot be inserted for some unknown reason (this
  // should never happen)
  return false;
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
void QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::remove(
    QuadTreeData<T> const& data)
{
  if (is_leaf()) {
    int remove_index = -1;
    // If we are dealing with a leaf, look for an object to remove
    for (size_t i = 0; i < m_contents.size(); ++i) {
      if (m_contents[i].object == data.object) {
        remove_index = (int)i;
        break;
      }
    }
    if (remove_index != -1) {
      auto it = m_contents.erase(m_contents.begin() + remove_index);
    }
  } else {
    for (auto&& child : m_children) {
      child.remove(data);
    }
  }
  shake();
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
void QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::update(
    QuadTreeData<T> const& data)
{
  remove(data);
  insert(data);
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
void QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::reset()
{
  if (is_leaf()) {
    for (auto&& content : m_contents) {
      content.flag = false;
    }
  } else {
    for (auto&& child : m_children) {
      child.reset();
    }
  }
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
void QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::shake()
{
  // If this node contains less than the maximum number of objects, we can
  // collapse all child nodes into this node
  if (!is_leaf() && num_objects() == 0) {
    m_children.clear();
    return;
  }

  if (num_objects() < MaxObjectsPerNode) {
    std::queue<QuadTreeNode<T, MaxDept, MaxObjectsPerNode>*> to_process;
    to_process.push(this);
    while (!to_process.empty()) {
      auto processing = to_process.back();
      if (!processing->is_leaf()) {
        for (auto&& child : m_children) {
          to_process.push(&child);
        }
      } else if (processing != this) {
        m_contents.insert(m_contents.end(), processing->m_contents.begin(),
                          processing->m_contents.end());
      }
      to_process.pop();
    }
    m_children.clear();
  }
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
void QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::split()
{
  if (current_depth() + 1 >= MaxDept)
    return;

  vec2 min    = m_node_bounds.get_min();
  vec2 max    = m_node_bounds.get_max();
  vec2 center = min + ((max - min) * 0.5f);

  auto ne = Rectangle2D::from_min_max({center.x, center.y}, {max.x, max.y});
  auto nw = Rectangle2D::from_min_max({min.x, center.y}, {center.x, max.y});
  auto sw = Rectangle2D::from_min_max({min.x, min.y}, {center.x, center.y});
  auto se = Rectangle2D::from_min_max({center.x, min.y}, {max.x, center.y});

  using Node = QuadTreeNode<T, MaxDept, MaxObjectsPerNode>;
  m_children.emplace_back(Node{ne, current_depth() + 1});
  m_children.emplace_back(Node{nw, current_depth() + 1});
  m_children.emplace_back(Node{sw, current_depth() + 1});
  m_children.emplace_back(Node{se, current_depth() + 1});
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
std::vector<QuadTreeData<T>*>
QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::query(Rectangle2D const& area)
{
  std::vector<QuadTreeData<T>*> result{};
  if (!area.intersects(m_node_bounds))
    return result;

  // Insert the object at this level
  for (auto&& content : m_contents) {
    if (area.intersects(content.bounds)) {
      assert(content.object);
      result.push_back(&content);
    }
  }
  // If there's not children, terminate here
  if (is_leaf()) {
    return result;
  }
  // Otherwise, query every child
  for (auto&& child : m_children) {
    auto recurse = child.query(area);
    if (!recurse.empty()) {
      result.insert(result.end(), recurse.begin(), recurse.end());
    }
  }
  return result;
}

template<typename T, int MaxDept, int MaxObjectsPerNode>
class QuadTree : public QuadTreeNode<T, MaxDept, MaxObjectsPerNode>
{
 public:
  using QuadTreeNode<T, MaxDept, MaxObjectsPerNode>::QuadTreeNode;
};
} // namespace isaac

#endif