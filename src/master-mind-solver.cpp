#include <docopt/docopt.h>
#include <fmt/format.h>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <map>
#include <memory>

#include "helpers.hpp"
#include "master-mind.hpp"
#include "solvers/brute-force.hpp"
#include "solvers/naive.hpp"
#include "solvers/solver.hpp"

using namespace helpers;

using SolverFactory = std::unique_ptr<Solver> (*)(const MasterMind&);

template<typename SolverType>
std::unique_ptr<Solver> solverFactory(const MasterMind& mm) {
  return std::unique_ptr<SolverType>(new SolverType{mm});
}

static const std::map<std::string, SolverFactory> solvers = {{"brute-force", &solverFactory<SolverBruteForce>},
                                                             {"naive", &solverFactory<SolverNaive>}};

static constexpr auto USAGE =
  R"(Usage: master-mind-solver [-h|--help] [-v|--verbose] [--list|SOLVER]

-h --help    Show this help info
-v --verbose Show detailed solver output
--list       List solvers)";

int main(int argc, char** argv) {
  const auto args    = docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, true);
  const auto verbose = args.at("-v").asBool() || args.at("--verbose").asBool();

  if (args.at("--list").asBool()) {
    std::ranges::for_each(solvers, [](const auto& solver) { fmt::print("{}\n", solver.first); });
  } else {
    auto solver_type = args.at("SOLVER").asString();
    if (solvers.find(solver_type) != solvers.end()) {
      MasterMind mm{generate_secret()};
      auto       solver = solvers.at(solver_type)(mm);
      fmt::print("Solver '{}' needed {} steps\n", solver_type, solver->solve(verbose));
    } else {
      fmt::print("Unknown solver type '{}', use '--list' to check out the available solvers.\n", solver_type);
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}