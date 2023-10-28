#pragma once

#include <format>
#include <string>
#include <iostream>

namespace otus_gfx
{

class Log
{
public:
  enum Severity
  {
    ERROR,
    WARN,
    INFO,
    DEBUG
  };

  static Log& Get()
  {
    static Log instance;
    return instance;
  }

  void SetSeverity(Severity level)
  {
    level_ = level;
  }

  template <typename... Args>
  static void PrintRaw(std::string_view fmt, Args&&... args)
  {
    std::cout << std::vformat(fmt, std::make_format_args(args...));
  }

  template <typename... Args>
  void Debug(std::string_view fmt, Args&&... args) noexcept
  {
    if (level_ < Severity::DEBUG)
      return;

    std::cout << "[DEBUG] ";
    PrintRaw(fmt, args...);
    std::cout << "\n";
  }

  template <typename... Args>
  void Info(std::string_view fmt, Args&&... args) noexcept
  {
    if (level_ < Severity::INFO)
      return;

    std::cout << "[INFO] ";
    PrintRaw(fmt, args...);
    std::cout << "\n";
  }

  template <typename... Args>
  void Warn(std::string_view fmt, Args&&... args) noexcept
  {
    if (level_ < Severity::WARN)
      return;

    std::cout << "[WARN] ";
    PrintRaw(fmt, args...);
    std::cout << "\n";
  }

  template <typename... Args>
  void Error(std::string_view fmt, Args&&... args) noexcept
  {
    std::cout << "[ERROR] ";
    PrintRaw(fmt, args...);
    std::cout << "\n";
  }

private:
  Severity level_ = Severity::WARN;

  Log() = default;
  ~Log() = default;

  Log(const Log& root) = delete;
  Log& operator=(const Log&) = delete;
  Log(Log&& root) = delete;
  Log& operator=(Log&&) = delete;
};

}  // namespace otus_gfx
