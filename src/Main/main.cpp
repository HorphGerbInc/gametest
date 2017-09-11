
#include <iostream>

#include <Common/CommandLineArguments.hpp>
#include <Common/Configuration.hpp>
#include <Common/constants.hpp>

/**/
int main(int argc, char *argv[]) {

  try {
    // Handle command line arguemnts
    jerobins::common::CommandLineArguments cli;
    cli.AddFlag("debug");
    cli.AddParameter("test");
    cli.Parse(argc, argv);

    // print them out
    std::cout << "Debug set: " << cli.FlagSet("debug");
    
  } catch (std::runtime_error &e) {
    std::cout << std::string(e.what()) << std::endl;
  }

  return EXIT_SUCCESS;
}