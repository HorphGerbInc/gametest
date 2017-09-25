
// STL
#include <fstream>
#include <sstream>
#include <streambuf>

// lib
#include <Common/Json.hpp>

// Mine
#include <Resource/VertexShader.hpp>
#include <Resource/ShaderFactory.hpp>

namespace jerobins {
  namespace resource {

    VertexShader::VertexShader(std::string name, std::string description, std::string version, std::string contents) {
      
    }

    bool VertexShader::Compile() {
      return compile(GL_VERTEX_SHADER);
    }

    VertexShader VertexShader::Load(std::string filename) {
      return ShaderFactory::LoadShader<VertexShader>(filename);
    }
    
  }
}
