
#include <Render/Sphere.hpp>

namespace jerobins {
  namespace render {

    Sphere::Sphere(float radius, size_t subdivisions) {
      if (subdivisions == 0) {
        // square
      }
    }

    const float *Sphere::Data() const { return &this->data[0]; }

    size_t Sphere::DataCount() const { return this->data.size(); }

    const size_t *Sphere::Indices() const { return &this->indices[0]; }

    size_t Sphere::IndicesCount() const { return this->indices.size(); }

    RenderType Sphere::Type() const { return RenderType::Triangles; }
  }
}