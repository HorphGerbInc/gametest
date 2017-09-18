
#ifndef _OPERATIONS_HPP
#define _OPERATIONS_HPP

namespace jerobins {
    namespace math {
        template<typename T>
        Clamp(T min, T max, T value) {
            if(value < min) return min;
            if(value > max) return max;
            return value;
        }

        // Linear interpolation between two points
        float LERP1D(float start, float end, float percent) {
            return start + (end - start) * percent;
        }

        Vec2 LERP2D(Vec2 start, Vec2 end, float percent) {
            float dx = end.X - start.X;
            float x = start.X + dx * percent;

            float dy = end.Y - start.Y;
            float y = start.y + dy * percent;

            return Vec2(x , y);
        }
    }
}

#endif