
#ifndef COLOR_HPP_
#define COLOR_HPP_

// Lib
#include <Resource/Json.hpp>

namespace jerobins {
  namespace render {
    /**
     * @brief Represents a RGBA color.
     *
     */
    struct Color {

      /**
       * @brief Creates the color black.
       *
       */
      Color();

      /**
       * @brief Creates a color based on the provided parameters.
       *
       * @param r Red in the range 0 to 1.
       * @param g Green in the range 0 to 1.
       * @param b Blue in the range 0 to 1.
       * @param a Alpha in the range 0 to 1.
       */
      Color(float r, float g, float b, float a);

      /**
       * @brief Red component.
       *
       */
      float Red = 0.0;

      /**
       * @brief Green component.
       *
       */
      float Green = 0.0;

      /**
       * @brief Blue component.
       *
       */
      float Blue = 0.0;

      /**
       * @brief Alpha component.
       *
       */
      float Alpha = 0.0;
    };

    // Json methods
    void to_json(nlohmann::json &j, const Color &input);
    void from_json(const nlohmann::json &j, Color &output);
  } // namespace render
} // namespace jerobins

#endif