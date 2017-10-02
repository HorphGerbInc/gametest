
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <map>

static const int BufferSize = 4096;
static char Buffer[BufferSize];

#ifdef _WIN32
#include <windows.h>
std::string GetFullPath(std::string name) {
  int len = GetFullPathName(name.c_str(), BufferSize, Buffer, NULL);
  Buffer[len] = 0;
  return std::string(Buffer);
}

#elif __linux__
#include <cstdio>

std::string GetFullPath(std::string name) {
  realpath(name.c_str(), Buffer);
  std::string result(Buffer);
  return result;
}

#else

#error "Unsupported OS"

#endif

#include <Common/Logger.hpp>

namespace jerobins {
  namespace common {

    static std::map<std::string, Logger> loggers;
    static std::map<jerobins::common::LoggingLevel, std::string> mapping = {
        {Debug, "Debug"},
        {Info, "Info"},
        {Warn, "Warn"},
        {Error, "Error"},
        {Fatal, "Fatal"}};

    Logger::Logger(std::ostream *output) : out(output) {}

    Logger::Logger(Logger &&other) {
      this->out = other.out;
      other.out = nullptr;
    }

    Logger::Logger(const Logger &other) { this->out = other.out; }

    Logger::~Logger() { out = nullptr; }

    void Logger::Log(std::string &msg, LoggingLevel level) {
      auto now = std::chrono::system_clock::now();
      auto in_time_t = std::chrono::system_clock::to_time_t(now);
      *out << "[" << mapping[level] << "]"
           << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << ": "
           << msg << std::endl;
    }

    Logger &Logger::operator=(const Logger &other) {
      this->out = other.out;
      return *this;
    }

    Logger *Logger::GetLogger(std::string filename) {
      filename = GetFullPath(filename);
      auto iter = loggers.find(filename);
      if (iter == loggers.end()) {
        Logger log(new std::ofstream(filename));
        loggers.insert(std::pair<std::string, Logger>(filename, log));
        iter = loggers.find(filename);
      }
      return &iter->second;
    }
  }
}