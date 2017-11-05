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

            template<class T>
            void Log(T && obj, LoggingLevel level = Info) {
                Log(obj , level);
            }

            template<class T>
            void Log(T & obj, LoggingLevel level = Info) {
                std::stringstream ss;
                ss << obj;
                Log(ss.str(), level);
            }

            void Log(std::string file, int line, std::string & msg, LoggingLevel level = Info);            
            void Log(std::string file, int line, std::string && msg, LoggingLevel level = Info);            
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