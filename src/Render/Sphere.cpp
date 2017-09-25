
#include <Render/Sphere.hpp>

namespace jerobins {
  namespace render {

    Sphere::Sphere(float radius, unsigned int subdivisions) {
      if (subdivisions == 0) {
        // square
      }
    }

    const float *Sphere::Data() const { return &this->data[0]; }

	unsigned int Sphere::DataCount() const { return (unsigned int)this->data.size(); }

    const unsigned int *Sphere::Indices() const { return &this->indices[0]; }

	unsigned int Sphere::IndicesCount() const { return (unsigned int)this->indices.size(); }

    RenderType Sphere::Type() const { return RenderType::Triangles; }
  }
}