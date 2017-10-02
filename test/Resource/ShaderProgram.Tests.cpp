
// StdLib
#include <iostream>

// Test framework
#include <catch.hpp>

// Jerobins
#include <Resource/ShaderProgram.hpp>

TEST_CASE("[ShaderProgram] : Can load json") {
  jerobins::resource::ShaderProgram program = jerobins::resource::ShaderProgram::Load("shaders/programs/default.json");

  REQUIRE(program.Version() == "0.1.0");
  REQUIRE(program.Name() == "default");
  REQUIRE(program.Description() == "Default program which just passes through the vertices and uses a default color of red.");
  
}
