

#include <Common/CommandLineArguments.hpp>
#include <gtest/gtest.h>

class CommandLineTest : public ::testing::Test {

public:
  void TEST_Constructor() {
    CommandLineArguments cli;
    CommandLineArguments *cli_ptr = new CommandLineArguments();
    ASSERT_NE(cli_ptr, nullptr);
  }

  int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
};