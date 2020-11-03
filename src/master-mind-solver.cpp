#include <docopt/docopt.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "helpers.hpp"
#include "master-mind.hpp"
#include "solvers/naive.hpp"

static constexpr auto USAGE =
  R"(Usage: master-mind-solver [-h|--help] [-v|--verbose]

-h --help    Show this help info
-v --verbose Show guess/secret/outcome
)";

int main(int argc, char** argv) {
  const auto args    = docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, true);
  const bool verbose = (args.find("-v") != args.end()) || (args.find("--verbose") != args.end());
  
  if (verbose) {
    std::cout << "Hoi" << '\n';
  }

  SolverNaive solver{MasterMind{helpers::generateRandomSecret()}};
  std::cout << solver.solve() << '\n';

  return EXIT_SUCCESS;
}
