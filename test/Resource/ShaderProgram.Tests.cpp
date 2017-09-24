
// StdLib
#include <iostream>

// Test framework
#include <catch.hpp>

// Jerobins
#include <Resource/ShaderProgram.hpp>

TEST_CASE("[ShaderProgram] : Can load json") {
  jerobins::resource::ShaderProgram program = jerobins::resource::ShaderProgram::Load("shaders/programs/default.json");

  REQUIRE(program.version == "0.1.0");
  REQUIRE(program.name == "default");
  REQUIRE(program.description == "Default program which just passes through the vertices and uses a default color of red.");
  REQUIRE(program.vertexShaders.size() == 1);
  REQUIRE(program.fragmentShaders.size() == 1);
  REQUIRE(program.vertexShaders[0] == "passthrough.vert");
  REQUIRE(program.fragmentShaders[0] == "red.frag");
  
}
