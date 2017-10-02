
#ifndef COLOR_HPP_
#define COLOR_HPP_

// Lib
#include <Resource/Json.hpp>

namespace jerobins {
  namespace render {
    struct Color {

      Color();
      Color(float r, float g, float b, float a);

      float Red = 0.0;
      float Green = 0.0;
      float Blue = 0.0;
      float Alpha = 0.0;
    };

    // Json methods
    void to_json(nlohmann::json &j, const Color &input);
    void from_json(const nlohmann::json &j, Color &output);
  }
}

#endif