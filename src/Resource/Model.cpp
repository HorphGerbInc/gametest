
// Stdlib
#include <fstream>

// Jerobins
#include <Common/Logger.hpp>
#include <Resource/Model.hpp>

// Lib
#include <Resource/Json.hpp>

namespace jerobins {
  namespace resource {

    Model::Model() { /* empty */
    }

    Model::Model(std::vector<jerobins::math::Vec3<float>> vertices,
                 jerobins::render::RenderType type, ShaderProgram program,
                 std::vector<int> indices,
                 std::vector<jerobins::render::Color> colors,
                 std::vector<jerobins::math::Vec3<float>> norms,
                 std::vector<jerobins::math::Vec2<int>> textCoords) {
      this->vertices = vertices;
      this->indices = indices;
      this->colors = colors;
      this->norms = norms;
      this->textCoords = textCoords;
      this->type = type;
      this->program = program;
    }

    void Model::Serialize(std::ostream &os,
                          jerobins::common::SerializationFormat format) const {
      nlohmann::json output;

      output["type"] = RenderTypeToString(this->type);
      output["vertices"] = this->vertices;
      output["indices"] = this->indices;
      output["colors"] = this->colors;
      output["normals"] = this->norms;
      output["textureCoordinates"] = this->textCoords;
      output["program"] = this->program.Name() + ".json";

      os << std::setw(4) << output;
    }

    Model Model::Deserialize(std::istream &is,
                             jerobins::common::SerializationFormat format) {
      nlohmann::json input;
      is >> input;

      Model result;

      // REQUIRED
      result.type = jerobins::render::StringToRenderType(input["type"]);

      jerobins::common::Logger::GetLogger()->Log("type read");
      result.vertices =
          input.at("vertices").get<std::vector<jerobins::math::Vec3<float>>>();
          jerobins::common::Logger::GetLogger()->Log("%uz", result.vertices.size());
          

      jerobins::common::Logger::GetLogger()->Log("vertices read");
      result.program = ShaderProgram::Load(
          ("shaders/programs/" + input["program"].get<std::string>()));

      jerobins::common::Logger::GetLogger()->Log("program read");

      // OPTIONAL
      if (!input.at("indices").is_null()) {
        result.indices = input.at("indices").get<std::vector<int>>();
        jerobins::common::Logger::GetLogger()->Log("indices read");
      }

      if (!input.at("colors").is_null()) {
        result.colors =
            input.at("colors").get<std::vector<jerobins::render::Color>>();
        jerobins::common::Logger::GetLogger()->Log("colors read");
      }
      if (!input.at("indices").is_null()) {
        result.norms =
            input.at("indices").get<std::vector<jerobins::math::Vec3<float>>>();
        jerobins::common::Logger::GetLogger()->Log("norms read");
      }

      if (!input.at("textureCoordinates").is_null()) {
        result.textCoords = input.at("textureCoordinates")
                                .get<std::vector<jerobins::math::Vec2<int>>>();
        jerobins::common::Logger::GetLogger()->Log("texture coordinates read");
      }
      jerobins::common::Logger::GetLogger()->Log("model read");

      return result;
    }

    Model Model::Load(std::string filename) {
      std::ifstream input(filename);
      if (input.is_open()) {
        return Model::Deserialize(input,
                                  jerobins::common::SerializationFormat::Text);
      }
      throw std::runtime_error("Could not open the file " + filename);
    }

    std::string Model::ToString() const { return "Model"; }
  }
}