#ifndef SYSTEM_OBSERVER_HPP
#define SYSTEM_OBSERVER_HPP

#include <algorithm>
#include <iostream>
#include <vector>

namespace isaac {
template<typename EventType>
class Observable;

template<typename EventType>
class Observer
{
 public:
  virtual ~Observer() = default;
  virtual void on_notify(Observable<EventType>& subject,
                         EventType const& event) {};
};

template<typename EventType>
class Observable
{
  std::vector<Observer<EventType>*> m_observers;

 public:
  void add_observer(Observer<EventType>& observer)
  {
    if (std::find(m_observers.begin(), m_observers.end(), &observer)
        != m_observers.end()) {
      std::cerr << "observer already registered\n";
      return;
    }
    m_observers.push_back(&observer);
  };

  void remove_observer(Observer<EventType>& observer)
  {
    auto n = std::erase(m_observers, &observer);
    if (n == 0) {
      std::cerr << "observer not found\n";
    }
  }

  void notify(EventType const& event)
  {
    for (auto& o : m_observers)
      o->on_notify(*this, event);
  }
};
} // namespace isaac

#endif