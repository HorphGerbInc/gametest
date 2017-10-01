
#include <Render/Color.hpp>

namespace jerobins {
  namespace render {

    void to_json(nlohmann::json &j, const Color &input) {
      j["red"] = input.Red;
      j["green"] = input.Green;
      j["blue"] = input.Blue;
      j["alpha"] = input.Alpha;
    }

    void from_json(const nlohmann::json &j, Color &output) {
      output.Red = j["red"];
      output.Green = j["green"];
      output.Blue = j["blue"];
      output.Alpha = j["alpha"];
    }
  }
}