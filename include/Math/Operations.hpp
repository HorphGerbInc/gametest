
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

        template<class V2>
        V2 LERP2D(const V2 & start, const V2 & end, float percent) {
            float dx = end.X() - start.X();
            float x = start.X() + dx * percent;

            float dy = end.Y() - start.Y();
            float y = start.Y() + dy * percent;

            return V2(x , y);
        }
    }
}

#endif