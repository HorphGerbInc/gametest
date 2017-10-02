
// STL
#include <fstream>
#include <sstream>
#include <streambuf>

// lib
#include <Resource/Json.hpp>

// Mine
#include <Common/FileUtil.hpp>
#include <Common/Logger.hpp>
#include <Resource/VertexShader.hpp>

namespace jerobins {
  namespace resource {

    VertexShader::VertexShader(std::string name, std::string description,
                               std::string version, std::string contents) {
      this->name = name;
      this->description = description;
      this->version = version;
      this->contents = contents;
    }

    bool VertexShader::Compile() { return compile(GL_VERTEX_SHADER); }

    VertexShader VertexShader::Load(std::string filename) {
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
          jerobins::common::FileUtil::ReadFile("shaders/vertex/" + name);

      jerobins::common::Logger::GetLogger()->Log(contents);
      VertexShader result(name, description, version, contents);
      return result;
    }
  }
}
