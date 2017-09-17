
// Stdlib
#include <map>

// Test
#include <catch.hpp>

// Project
#include <Common/CommandLineArguments.hpp>

TEST_CASE("Can create on heap", "[CommandLineArguments]") {
  jerobins::common::CommandLineArguments *cli_ptr =
      new jerobins::common::CommandLineArguments();
  REQUIRE(cli_ptr != nullptr);
  delete cli_ptr;
}

TEST_CASE("Can create on stack", "[CommandLineArguments]") {
  jerobins::common::CommandLineArguments cli;
}

TEST_CASE("Can create flags", "[CommandLineArguments]") {
  int argc = 2;
  char *argv[] = {"ERROR", "-debug"};

  jerobins::common::CommandLineArguments cli;
  cli.AddFlag("debug");
  REQUIRE(cli.FlagSet("debug") == false);
  cli.Parse(argc, argv);
  REQUIRE(cli.FlagSet("debug") == true);
}

struct CLIRun {
  std::vector<char *> args;
  std::vector<std::string> flags;
  std::vector<std::string> parameters;

  std::vector<std::string> setFlags;
  std::map<std::string, std::string> kvps;
};

TEST_CASE("Can create parameters", "[CommandLineArguements]") {

  std::vector<CLIRun> runs = {
      {
          {"ERROR", "-Filename", "bob"}, // argv
          {},                            // flags
          {"Filename"},                  // parameters
          {},                            // setFlags
          {{"Filename", "bob"}}          // kvps
      },
      {
          {"ERROR", "-Filename", "bob"}, // argv
          {"Debug"},                     // flags
          {"Filename", "Name"},          // parameters
          {},                            // setFlags
          {{"Filename", "bob"}}          // kvps
      },
      {
          {"ERROR", "-Filename", "bob", "-debug"}, // argv
          {"debug"},                               // flags
          {"Filename", "Name"},                    // parameters
          {"debug"},                               // setFlags
          {{"Filename", "bob"}}                    // kvps
      },
      {
          {"ERROR", "-Filename=bob", "debug"}, // argv
          {"debug"},                           // flags
          {"Filename", "Name"},                // parameters
          {"debug"},                           // setFlags
          {{"Filename", "bob"}}                // kvps
      },
      {
          {"ERROR", "Filename", "bob"}, // argv
          {},                           // flags
          {"Filename", "Name"},         // parameters
          {},                           // setFlags
          {{"Filename", "bob"}}         // kvps
      },
      {
          {"ERROR", "Filename=bob"}, // argv
          {},                        // flags
          {"Filename", "Name"},      // parameters
          {},                        // setFlags
          {{"Filename", "bob"}}      // kvps
      }};

  for (auto run : runs) {

    jerobins::common::CommandLineArguments cli;

    // Flags
    for (auto flag : run.flags) {
      cli.AddFlag(flag);
      REQUIRE(cli.FlagSet(flag) == false);
    }
    for (auto flag : run.flags) {
      REQUIRE(cli.FlagSet(flag) == false);
    }

    // Parameters
    for (auto parameter : run.parameters) {
      cli.AddParameter(parameter);
      REQUIRE(cli.ParameterSet(parameter) == false);
      for (auto flag : run.flags) {
        REQUIRE(cli.FlagSet(flag) == false);
      }
    }
    for (auto flag : run.flags) {
      REQUIRE(cli.FlagSet(flag) == false);
    }
    for (auto parameter : run.parameters) {
      REQUIRE(cli.ParameterSet(parameter) == false);
    }

    // Parse
    cli.Parse((int)run.args.size(), &run.args[0]);

    // Validate
    for (auto flag : run.setFlags) {
      REQUIRE(cli.FlagSet(flag) == true);
    }
    for (auto kvp : run.kvps) {
      REQUIRE(cli.ParameterSet(kvp.first) == true);
      if (cli.ParameterSet(kvp.first)) {
        REQUIRE(cli.ParameterValue(kvp.first) == kvp.second);
      }
    }

    for (auto parameter : run.parameters) {
      if (run.kvps.find(parameter) == run.kvps.end()) {
        REQUIRE(cli.ParameterSet(parameter) == false);
      }
    }
  }
}
