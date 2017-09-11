
#include <iostream>

#include <common/CommandLineArguments.hpp>
#include <common/Configuration.hpp>
#include <common/constants.hpp>

/**/
int main(int argc, char *argv[]) {

  jerobins::common::CommandLineArguments cli;
  cli.AddFlag("debug");
  cli.AddParameter("test");
  cli.Parse(argc, argv);

  std::cout << "Debug set: " << cli.FlagSet("debug");

  return EXIT_SUCCESS;
}