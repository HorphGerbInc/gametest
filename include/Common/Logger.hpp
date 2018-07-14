#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <memory>
#include <sstream>

namespace jerobins {
  namespace common {

    /**
     * @brief Supported logging levels.
     *
     * @detailed Supported logging levels.
     *  - Debug - Debugging information.
     *  - Info  - Information on what is happening.
     *  - Warn  - Warning to the user or developer.
     *  - Error - An error has occurred.
     *  - Fatal - The program hs encountered a fatal error.
     */
    enum LoggingLevel { Debug, Info, Warn, Error, Fatal };

    /**
     * @brief   Basic logging class.
     *
     */
    class Logger {
    public:
      /**
       * @brief Copy constructor.
       *
       * @param other   Other logger we copy.
       */
      Logger(Logger &&other);

      /**
       * @brief Copy constructor.
       *
       * @param other   Other logger we copy.
       */
      Logger(const Logger &other);

      /**
       * @brief Deconstructor.
       *
       */
      ~Logger();

      /**
       * @brief Log a message.
       *
       * @param level   The level we want to log the message at.
       * @param format The format string containing the message.
       * @param ...     The parameters to the format string.
       */
      void Log(LoggingLevel level, std::string format, ...);

      /**
       * @brief Log a message at the default logging level.
       *
       * @param format The format string containing the message.
       * @param ...    The parameters to the format string.
       */
      void Log(std::string format, ...);

      /**
       * @brief Create a logger for the specific file.
       *
       * @param filename    The filename to log to.
       * @return Logger*    The logging object.
       */
      static Logger *GetLogger(std::string filename = "output.log");

      /**
       * @brief Copy another logger to myself.
       *
       * @return Logger&    The logger to copy from.
       */
      Logger &operator=(const Logger &);

    private:
      std::shared_ptr<std::ostream> out;
      Logger(std::ostream *os);

    public:
    /**
     * @brief The default logging level.
     * 
     */
      LoggingLevel DefaultLoggingLevel = Info;
    };
  } // namespace common
} // namespace jerobins

#endif