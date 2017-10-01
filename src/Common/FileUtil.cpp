
#include <fstream>
#include <string>

#include <Common/FileUtil.hpp>

namespace jerobins {
  namespace common {
    std::string FileUtil::ReadFile(const std::string &filename) {
      std::ifstream input(filename);
      if (input.is_open()) {
        std::string content((std::istreambuf_iterator<char>(input)),
                            (std::istreambuf_iterator<char>()));
        return content;
      }
      throw std::runtime_error("Could not open file " + filename);
    }

    std::string FileUtil::GetFileName(const std::string &filename) {
      auto found = filename.find_last_of("/\\");
      return filename.substr(found + 1);
    }

    std::string FileUtil::GetDirectory(const std::string &filename) {
      auto found = filename.find_last_of("/\\");
      return filename.substr(0, found);
    }
  }
}
