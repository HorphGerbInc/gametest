
// STL
#include <fstream>
#include <sstream>
#include <streambuf>

// lib
#include <Resource/Json.hpp>

// Mine
#include <Common/FileUtil.hpp>
#include <Common/Logger.hpp>
#include <Resource/FragmentShader.hpp>

namespace jerobins {
  namespace resource {

    FragmentShader::FragmentShader(std::string name, std::string description,
                                   std::string version, std::string contents) {
      this->name = name;
      this->description = description;
      this->version = version;
      this->contents = contents;
    }

    bool FragmentShader::Compile() { return compile(GL_FRAGMENT_SHADER); }

    FragmentShader FragmentShader::Load(std::string filename) {
      nlohmann::json j = LoadJson(filename);

      jerobins::resource::ThrowIfFieldNotSet(j, "version");
      jerobins::resource::ThrowIfFieldNotSet(j, "name");
      jerobins::resource::ThrowIfFieldNotSet(j, "description");
      jerobins::resource::ThrowIfFieldNotSet(j, "type");

      std::string version = j["version"];
      std::string name = j["name"];
      std::string description = j["description"];
      std::string type = j["type"];
      std::string contents =
          jerobins::common::FileUtil::ReadFile("shaders/fragment/" + name);

      jerobins::common::Logger::GetLogger()->Log(contents);
      FragmentShader result(name, description, version, contents);
      return result;
    }
  }
}