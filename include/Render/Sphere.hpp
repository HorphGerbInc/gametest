
#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include <vector>

#include <Render/IRenderable.hpp>

namespace jerobins {
  namespace render {
    class Sphere : public IRenderable {
    public:
      // Construct a new spehere
      Sphere(float radius, unsigned int subdivisions);

      // Raw underlying data
      virtual const float *Data() const = 0;
      virtual unsigned int DataCount() const = 0;

      // Indices, if specified, null if not.
      virtual const unsigned int *Indices() const = 0;
      virtual unsigned int IndicesCount() const = 0;

      // The structure of the data
      virtual RenderType Type() const = 0;

    private:
      std::vector<float> data;
      std::vector<unsigned int> indices;
    };
  }
}

#endif