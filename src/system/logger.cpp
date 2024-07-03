#include "system/logger.hpp"

#include <chrono>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

#define USE_STDERR

namespace isaac {
LoggerService::LoggerService(Level log_level, std::string fmt)
    : m_log_level{log_level}
    , m_fmt{std::move(fmt)}
{}

std::string LoggerService::get_current_time() const
{
  auto const now = std::chrono::system_clock::now();
  auto t         = std::chrono::system_clock::to_time_t(now);
  std::tm l_time{};
  localtime_r(&t, &l_time);
  std::stringstream ss{};
  ss << std::put_time(&l_time, m_fmt.c_str());
  return ss.str();
}

// Logger
Logger::Logger(Level logLevel, std::string fmt)
    : LoggerService{logLevel, std::move(fmt)}
{}

void Logger::log(std::string_view const& msg, Level log_level) const
{
  if (log_level < m_log_level)
    return;
  auto current_time = get_current_time();
  auto const message =
      std::format("[{}] - {} - {}", current_time, k_levels[log_level], msg);

#ifdef USE_STDERR
  std::cerr << message << '\n';
#elif
  std::cout << message << '\n';
#endif
}

void Logger::debug(std::string_view const& msg) const
{
  log(msg, DEBUG);
}
void Logger::info(std::string_view const& msg) const
{
  log(msg, INFO);
}
void Logger::warn(std::string_view const& msg) const
{
  log(msg, WARN);
}
void Logger::error(std::string_view const& msg) const
{
  log(msg, ERROR);
}
} // namespace isaac
