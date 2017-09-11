
#include <Render/Sphere.hpp>

namespace jerobins {
  namespace render {

    Sphere::Sphere(float radius, std::size_t subdivisions) {
      if (subdivisions == 0) {
        // square
      }
    }

    const float *Sphere::Data() const { return &this->data[0]; }

    std::size_t Sphere::DataCount() const { return this->data.size(); }

    const std::size_t *Sphere::Indices() const { return &this->indices[0]; }

    std::size_t Sphere::IndicesCount() const { return this->indices.size(); }

    RenderType Sphere::Type() const { return RenderType::Triangles; }
  }
}