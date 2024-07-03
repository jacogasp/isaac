#ifndef CYCLIC_ITERATOR_HPP
#define CYCLIC_ITERATOR_HPP

namespace isaac {

template<typename T>
struct cyclic_iterator
{
 private:
  T m_head;
  T m_begin;
  T m_end;

 public:
  cyclic_iterator(T begin, T end)
      : m_head{begin}
      , m_begin{begin}
      , m_end{end} {};
  T begin()
  {
    return m_begin;
  }
  T end()
  {
    return m_end;
  }

  cyclic_iterator& operator++(int)
  {
    ++m_head;
    if (m_head == m_end) {
      m_head = m_begin;
    }
    return *this;
  }
  cyclic_iterator& operator--(int)
  {
    --m_head;
    if (m_head == m_end) {
      m_head = m_begin;
    }
    return *this;
  }

  auto operator*()
  {
    return *m_head;
  }

  friend bool operator==(T const& lhs, T const& rhs)
  {
    return lhs.it == rhs.it;
  }
  friend bool operator!=(T const& lhs, T const& rhs)
  {
    return !(lhs == rhs);
  }
};
} // namespace isaac
#endif
