#include "solver.hpp"

#include <fmt/format.h>

#include "../helpers.hpp"

Solver::Solver(const MasterMind& game, bool verbose)
  : game_{game}
  , verbose_{verbose} {
}

Score Solver::check(const Secret& secret) {
  number_of_tries_++;

  if (verbose_) {
    fmt::print("Trying secret #{}: [{}]..\n", number_of_tries_, helpers::to_string(secret));
  }

  return game_.guess(secret);
}
