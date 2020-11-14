#include "brute-force.hpp"

#include <fmt/format.h>

#include <cmath>

#include "../helpers.hpp"
#include "../master-mind.hpp"

SolverBruteForce::SolverBruteForce(const MasterMind& game, bool verbose)
  : Solver{game, verbose} {
}

unsigned long SolverBruteForce::solve() {
  auto guess_scalar = 0ul;
  while (true) {
    Secret guess{};
    auto   remainder = guess_scalar++;

    for (unsigned int field = NUMBER_OF_FIELDS; (field != 0u) && (remainder != 0); field--) {
      auto exponent    = static_cast<unsigned long>(std::pow(NUMBER_OF_COLORS, field - 1));
      auto coefficient = remainder / exponent;
      remainder -= (coefficient == 0ul ? 0ul : coefficient * exponent);
      guess[field - 1] = static_cast<Color>(coefficient);
    }

    if (helpers::win(check(guess))) {
      return number_of_tries_;
    }
  }
}
