
#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <json.hpp>

namespace jerobins {
  namespace render {
    class Color {
    public:
      Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f)
          : Red(r), Green(g), Blue(b), Alpha(a) { /* Empty */
      }

      float Red = 0.0;
      float Green = 0.0;
      float Blue = 0.0;
      float Alpha = 0.0;
    };

    void to_json(nlohmann::json &j, const Color &input);
    void from_json(const nlohmann::json &j, Color &output);
  }
}

#endif