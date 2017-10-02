
#ifndef _OPERATIONS_HPP
#define _OPERATIONS_HPP

namespace jerobins {
  namespace math {

    // Common math operations
    class Operations {
    public:
      // Clamp a value between two other values
      // assumes min <= max
      template <typename T> static T Clamp(T min, T max, T value) {
        if (value < min)
          return min;
        if (value > max)
          return max;
        return value;
      }

      // Linear interpolation between two points in one dimension
      float LERP1D(float start, float end, float percent) {
        return start + (end - start) * percent;
      }

      // Linear interpolation between two points in two dimensions
      template <class V2>
      static V2 LERP2D(const V2 &start, const V2 &end, float percent) {
        float dx = end.X() - start.X();
        float x = start.X() + dx * percent;

        float dy = end.Y() - start.Y();
        float y = start.Y() + dy * percent;

        return V2(x, y);
      }
    };
  }
}

#endif