#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <memory>

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

            void Log(std::string & msg, LoggingLevel level = Info);
            void Log(std::string && msg, LoggingLevel level = Info) {Log(msg, level);}
            
            
            static Logger* GetLogger(std::string filename = "output.log");
            
            Logger& operator=(const Logger&);
        private:
            std::shared_ptr<std::ostream> out;
            Logger(std::ostream* os);
        };
    }
}

#endif