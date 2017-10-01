

// StdLib
#include <iostream>
#include <fstream>
#include <vector>

// Test framework
#include <catch.hpp>

// Jerobins
#include <Resource/Model.hpp>
#include <Resource/ShaderProgram.hpp>
#include <Common/ISerializable.hpp>
#include <Math/Vec3.hpp>

using namespace jerobins::math;

TEST_CASE("[Model] : Can write json") {
  std::vector<jerobins::math::Vec3<float>> vertices = {
      Vec3<>(-0.5f, -0.5f, -0.5f), Vec3<>(-0.5f, -0.5f, -0.5f),
      Vec3<>(-0.5f, -0.5f, -0.5f),
  };
  auto type = jerobins::render::RenderType::Triangles;
  auto program = jerobins::resource::ShaderProgram::Load("shaders/programs/default.json");
  // Create
  jerobins::resource::Model model(vertices, type, program);

  // Write
  auto os = std::ofstream("tmp.json");
  auto format = jerobins::common::SerializationFormat::Text;
  model.Serialize(os, format);
}

TEST_CASE("[Model] : Can load json") {
  jerobins::resource::Model model =
      jerobins::resource::Model::Load("models/red_triangle.json");
}
