#ifndef SYSTEM_LOGGER_HPP
#define SYSTEM_LOGGER_HPP

#include <array>
#include <string>
#include <string_view>

namespace isaac {

class LoggerService
{
 public:
  enum Level
  {
    DEBUG,
    INFO,
    WARN,
    ERROR
  };

 protected:
  Level m_log_level;
  std::string m_fmt;
  [[nodiscard]] std::string get_current_time() const;

  static constexpr std::array k_levels{"DEBUG", "INFO", "WARN", "ERROR"};

 public:
  explicit LoggerService(Level logLevel  = INFO,
                         std::string fmt = "%Y-%m-%d %H:%M:%S");
  virtual ~LoggerService() = default;

  virtual void log(std::string_view const& msg, Level log_level) const = 0;
  virtual void debug(std::string_view const& msg) const                = 0;
  virtual void info(std::string_view const& msg) const                 = 0;
  virtual void warn(std::string_view const& msg) const                 = 0;
  virtual void error(std::string_view const& msg) const                = 0;
};

class LoggerNull : public LoggerService
{
 public:
  void log(std::string_view const& msg, Level logLevel) const final
  {}
  void debug(std::string_view const& msg) const final
  {}
  void info(std::string_view const& msg) const final
  {}
  void warn(std::string_view const& msg) const final
  {}
  void error(std::string_view const& msg) const final
  {}
};

class Logger : public LoggerService
{
 public:
  explicit Logger(Level log_level = INFO,
                  std::string fmt = "%Y-%m-%d %H:%M:%S");
  void log(std::string_view const& msg, Level log_level) const override;
  void debug(std::string_view const& msg) const override;
  void info(std::string_view const& msg) const override;
  void warn(std::string_view const& msg) const override;
  void error(std::string_view const& msg) const override;
};
} // namespace isaac
#endif
