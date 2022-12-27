#include <docopt/docopt.h>
#include <fmt/core.h>

#include <algorithm>
#include <cstdlib>
#include <map>
#include <memory>

#include "helpers.hpp"
#include "master-mind.hpp"
#include "solvers/brute-force.hpp"
#include "solvers/knuth.hpp"
#include "solvers/naive.hpp"
#include "solvers/solver.hpp"

using namespace helpers;

using SolverFactory = std::unique_ptr<Solver> (*)(const MasterMind&, bool verbose);

template<typename SolverType>
std::unique_ptr<Solver> solverFactory(const MasterMind& mm, bool verbose) {
  return std::unique_ptr<SolverType>(new SolverType{mm, verbose});
}

const std::map<std::string, SolverFactory> solvers = {
  {"brute-force", &solverFactory<SolverBruteForce>}, {"knuth", &solverFactory<SolverKnuth>}, {"naive", &solverFactory<SolverNaive>}};

constexpr auto USAGE =
  R"(Usage: master-mind-solver [-h|--help] [-q|--quiet] [-v|--verbose] [--list|SOLVER]

-h --help    Show this help info
-q --quiet   Show only the number of tries needed
-v --verbose Show detailed solver output
--list       List solvers)";

int main(int argc, char** argv) {
  const auto args        = docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, true);
  const auto quiet       = args.at("-q").asBool() || args.at("--quiet").asBool();
  const auto verbose     = args.at("-v").asBool() || args.at("--verbose").asBool();
  const auto solver_type = (args.at("SOLVER") ? args.at("SOLVER").asString() : "");

  if (args.at("--list").asBool()) {
    std::ranges::for_each(solvers, [](const auto& solver) { fmt::print("{}\n", solver.first); });
    return EXIT_SUCCESS;
  }

  if (solvers.find(solver_type) == solvers.end()) {
    fmt::print("Unknown solver type '{}', use '--list' to check out the available solvers.\n", solver_type);
    return EXIT_FAILURE;
  }

  MasterMind mm{generate_secret()};
  auto       solver = solvers.at(solver_type)(mm, verbose);

  if (quiet) {
    fmt::print("{}", solver->solve());
  } else {
    fmt::print("Solver '{}' needed {} steps\n", solver_type, solver->solve());
  }

  return EXIT_SUCCESS;
}
