
#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include <vector>

#include <Render/IRenderable.hpp>

namespace jerobins {
  namespace render {
    class Sphere : public IRenderable {
    public:
      /**
       * @brief Construct a new sphere with a given radius and number of
       * subdivisions.
       *
       * @param radius        Radius of the sphere.
       * @param subdivisions  Number of subdivisions.
       */
      Sphere(float radius, unsigned int subdivisions);

      /**
       * @brief Raw underlying vectices.
       *
       * @return const float* Array of vectices.
       */
      virtual const float *Data() const = 0;

      /**
       * @brief Number of vectices.
       *
       * @return unsigned int Number of vertices.
       */
      virtual unsigned int DataCount() const = 0;

      /**
       * @brief Indices if any.
       *
       * @return const unsigned int* Array of indices.
       */
      virtual const unsigned int *Indices() const = 0;

      /**
       * @brief Number of vectices if any.
       *
       * @return unsigned int Number of vectices.
       */
      virtual unsigned int IndicesCount() const = 0;

      /**
       * @brief Render type for the sphere.
       *
       * @return RenderType Render type.
       */
      virtual RenderType Type() const = 0;

    private:
      std::vector<float> data;
      std::vector<unsigned int> indices;
    };
  } // namespace render
} // namespace jerobins

#endif