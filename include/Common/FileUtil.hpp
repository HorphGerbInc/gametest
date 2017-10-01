
#ifndef FILEUTIL_HPP_
#define FILEUTIL_HPP_

namespace jerobins {
  namespace common {
    class FileUtil {
    public:
      static std::string ReadFile(const std::string & filename);
      static std::string GetDirectory(const std::string & filename);
      static std::string GetFileName(const std::string & filename);
    };
  }
}

#endif