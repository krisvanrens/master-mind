#include "knuth.hpp"

#include <fmt/format.h>

#include "../master-mind.hpp"

SolverKnuth::SolverKnuth(const MasterMind& game, bool verbose)
  : Solver{game, verbose} {
}

unsigned long SolverKnuth::solve() {
  // TODO

  return number_of_tries_;
}
