
#include <Render/Color.hpp>

namespace jerobins {
  namespace render {

    Color::Color() : Red(0), Green(0), Blue(0), Alpha(0) { /* Empty */
    }

    Color::Color(float r, float g, float b, float a)
        : Red(r), Green(g), Blue(b), Alpha(a) {
      /* Empty */
    }

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