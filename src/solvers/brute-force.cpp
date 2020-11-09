#include "brute-force.hpp"

#include <fmt/format.h>

#include <cmath>

#include "../helpers.hpp"
#include "../master-mind.hpp"

using namespace helpers;

SolverBruteForce::SolverBruteForce(const MasterMind& game)
  : Solver{game} {
}

unsigned long SolverBruteForce::solve(bool verbose) {
  while (true) {
    Secret      guess{};
    static auto guess_scalar = 0ul;
    auto        remainder    = guess_scalar++;

    for (unsigned int field = NUMBER_OF_FIELDS; (field != 0u) && (remainder != 0); field--) {
      auto exponent    = static_cast<unsigned long>(std::pow(NUMBER_OF_COLORS, field - 1));
      auto coefficient = remainder / exponent;
      remainder -= (coefficient == 0ul ? 0ul : coefficient * exponent);
      guess[field - 1] = static_cast<Color>(coefficient);
    }

    if (verbose) {
      fmt::print("Trying guess #{}: [{}]..\n", guess_scalar, to_string(guess));
    }

    if (win(game_.guess(guess))) {
      return guess_scalar;
    }
  }
}
