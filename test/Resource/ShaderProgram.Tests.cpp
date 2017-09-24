
// StdLib
#include <iostream>

// Test framework
#include <catch.hpp>

// Jerobins
#include <Resource/ShaderProgram.hpp>

TEST_CASE("[ShaderProgram] : Can load json") {
  jerobins::resource::ShaderProgram program = jerobins::resource::ShaderProgram::Load("shaders/programs/default.json");
}
