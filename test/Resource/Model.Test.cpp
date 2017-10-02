

// StdLib
#include <fstream>
#include <iostream>
#include <vector>

// Test framework
#include <catch.hpp>

// Jerobins
#include <Common/ISerializable.hpp>
#include <Common/Logger.hpp>
#include <Math/Vec3.hpp>
#include <Resource/Model.hpp>
#include <Resource/ShaderProgram.hpp>

using namespace jerobins::math;

TEST_CASE("[Model] : Can write json") {
  // Write
  std::vector<jerobins::math::Vec3<float>> vertices = {
      Vec3<>(-0.5f, -0.5f, -0.5f), Vec3<>(-0.5f, -0.5f, -0.5f),
      Vec3<>(-0.5f, -0.5f, -0.5f),
  };
  auto type = jerobins::render::RenderType::Triangles;
  auto program =
      jerobins::resource::ShaderProgram::Load("shaders/programs/default.json");
  // Create
  jerobins::resource::Model model(vertices, type, program);

  // Write
  {
    auto os = std::ofstream("tmp.json");
    auto format = jerobins::common::SerializationFormat::Text;
    model.Serialize(os, format);
    os.close();
  }

  // Read
  auto read = jerobins::resource::Model::Load("tmp.json");
  jerobins::common::Logger::GetLogger()->Log("back in the test");

  REQUIRE(read.VertexCount() == model.VertexCount());
  REQUIRE(read.ColorCount() == model.ColorCount());
  REQUIRE(read.NormalCount() == model.NormalCount());
  REQUIRE(read.TextureCount() == model.TextureCount());
  REQUIRE(read.Type() == model.Type());
  REQUIRE(read.Program().Name() == model.Program().Name());
}

TEST_CASE("[Model] : Can load json") {
  jerobins::resource::Model model =
      jerobins::resource::Model::Load("models/red_triangle.json");
}
