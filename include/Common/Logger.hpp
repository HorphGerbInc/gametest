#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <memory>
#include <sstream>

namespace jerobins {
    namespace common {

        enum LoggingLevel {
            Debug, Info, Warn, Error, Fatal
        };

        class Logger {
        public:
            Logger( Logger && other);
            Logger(const Logger & other);
            ~Logger();

            void Log(LoggingLevel level, std::string format, ...);            
            void Log(std::string format, ...);            
            
            static Logger* GetLogger(std::string filename = "output.log");
            
            Logger& operator=(const Logger&);
        private:
            std::shared_ptr<std::ostream> out;
            Logger(std::ostream* os);
        };
    }
}

#endif