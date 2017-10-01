
#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <vector>

#include <Common/ISerializable.hpp>
#include <Render/IRenderable.hpp>
#include <Resource/ShaderProgram.hpp>

namespace jerobins {
  namespace resource {

    class Model : public jerobins::render::IRenderable,
                  public jerobins::common::ISerializable<Model>,
                  public IResource<Model> {
    public:
      /* IRenderable */

      virtual const jerobins::math::Vec3<float> *GetVertices() const {
        return &vertices[0];
      };
      virtual unsigned int VertexCount() const {
        return this->vertices.size();
      };

      // Color of vertices
      virtual const jerobins::render::Color *GetColors() const {
        return &colors[0];
      };
      virtual unsigned int ColorCount() const { return this->colors.size(); };

      // normal of vertices
      virtual const jerobins::math::Vec3<float> *GetNormals() const {
        return &norms[0];
      };
      virtual unsigned int NormalCount() const { return this->norms.size(); };

      // Textures
      virtual const jerobins::math::Vec2<int> *GetTexureCoords() const {
        return &textCoords[0];
      }
      virtual unsigned int TextureCount() const { return textCoords.size(); }

      // Indices
      virtual const int *GetIndices() const { return &indices[0]; }
      virtual unsigned int IndicesCount() const { return indices.size(); }

      // The structure of the data
      virtual jerobins::render::RenderType Type() const { return type; }

      /* ISerializable */
      virtual void
      Serialize(std::ostream &os,
                jerobins::common::SerializationFormat format) const;

      static Model Deserialize(std::istream &is,
                               jerobins::common::SerializationFormat format);

      /* IResource */

      static Model Load(std::string filename);

      virtual std::string ToString() const;

      Model(std::vector<jerobins::math::Vec3<float>> vertices,
            jerobins::render::RenderType type, ShaderProgram program,
            std::vector<int> indices = {},
            std::vector<jerobins::render::Color> colors = {},
            std::vector<jerobins::math::Vec3<float>> norms = {},
            std::vector<jerobins::math::Vec2<int>> textCoords = {});

    private:
      Model();

      std::vector<jerobins::math::Vec3<float>> vertices;
      std::vector<int> indices;
      std::vector<jerobins::render::Color> colors;
      std::vector<jerobins::math::Vec3<float>> norms;
      std::vector<jerobins::math::Vec2<int>> textCoords;
      jerobins::render::RenderType type;
      ShaderProgram program;
    };
  }
}

#endif