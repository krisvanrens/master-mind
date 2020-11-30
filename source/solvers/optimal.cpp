#include "optimal.hpp"

#include <fmt/format.h>

#include <cmath>

#include "../helpers.hpp"
#include "../master-mind.hpp"

SolverOptimal::SolverOptimal(const MasterMind& game, bool verbose)
  : Solver{game, verbose} {
}

unsigned long SolverOptimal::solve() {
  // TODO

  return number_of_tries_;
}
