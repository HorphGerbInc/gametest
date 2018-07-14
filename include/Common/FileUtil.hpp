
#ifndef FILEUTIL_HPP_
#define FILEUTIL_HPP_

#include <string>

namespace jerobins {
  namespace common {
    class FileUtil {
    public:
      /**
       * @brief Read the entire file.
       *
       * @param path      The path to the file.
       * @return std::string  The contents of the file.
       */
      static std::string ReadFile(const std::string &path);

      /**
       * @brief Get the directory the file is located in.
       *
       * @param path          The path to the file.
       * @return std::string  The fully path to the directory.
       */
      static std::string GetDirectory(const std::string &path);

      /**
       * @brief     Return the name of the file..
       *
       * @param path          The path to the file.
       * @return std::string  The name of the file.
       */
      static std::string GetFileName(const std::string &path);
    };
  } // namespace common
} // namespace jerobins

#endif