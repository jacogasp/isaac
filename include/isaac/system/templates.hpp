#ifndef ISAAC_SYSTEM_TEMPLATES_HPP
#define ISAAC_SYSTEM_TEMPLATES_HPP

template<typename... Ts>
struct overloads : Ts...
{
  using Ts::operator()...;
};

template<typename... Ts>
overloads(Ts...) -> overloads<Ts...>;

#endif // ISAAC_SYSTEM_TEMPLATES_HPP
