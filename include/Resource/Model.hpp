
#ifndef MODEL_HPP_
#define MODEL_HPP_

// StdLib
#include <vector>

// Jerobins
#include <Common/ISerializable.hpp>
#include <Render/IRenderable.hpp>

namespace jerobins {
  namespace resource {

    class Model : public jerobins::render::IRenderable,
                  public jerobins::common::ISerializable<Model>,
                  public IResource<Model> {
    public:
      /* IRenderable */

      /**
       * @brief
       *
       * @return const jerobins::math::Vec3<float>*
       */
      virtual const jerobins::math::Vec3<float> *GetVertices() const;

      virtual unsigned int VertexCount() const;

      // Color of vertices
      virtual const jerobins::render::Color *GetColors() const;

      virtual unsigned int ColorCount() const;

      // normal of vertices
      virtual const jerobins::math::Vec3<float> *GetNormals() const;

      virtual unsigned int NormalCount() const;

      // Textures
      virtual const jerobins::math::Vec2<int> *GetTexureCoords() const;

      virtual unsigned int TextureCount() const;

      // Indices
      virtual const int *GetIndices() const;

      virtual unsigned int IndicesCount() const;

      // The structure of the data
      virtual jerobins::render::RenderType Type() const;

      virtual const jerobins::resource::ShaderProgram Program() const;

      /* ISerializable */
      virtual void
      Serialize(std::ostream &os,
                jerobins::common::SerializationFormat format) const;

      static Model Deserialize(std::istream &is,
                               jerobins::common::SerializationFormat format);

      virtual bool
      SupportsFormat(jerobins::common::SerializationFormat format) const;

      /* IResource */

      static Model Load(std::string filename);

      virtual void Save(std::string filename) const;

      virtual std::string ToString() const;

      Model(std::vector<jerobins::math::Vec3<float>> vertices,
            jerobins::render::RenderType type, ShaderProgram program,
            std::vector<int> indices = {},
            std::vector<jerobins::render::Color> colors = {},
            std::vector<jerobins::math::Vec3<float>> norms = {},
            std::vector<jerobins::math::Vec2<int>> textCoords = {});

    private:
      Model();
    };
  } // namespace resource
} // namespace jerobins

#endif