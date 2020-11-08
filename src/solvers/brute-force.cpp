#include "brute-force.hpp"

#include <fmt/format.h>

#include <cmath>

#include "../helpers.hpp"
#include "../master-mind.hpp"

SolverBruteForce::SolverBruteForce(const MasterMind& game)
  : Solver{game} {
}

unsigned long SolverBruteForce::solve(bool verbose) {
  Secret guess{};

  const auto guess_scalar_max = static_cast<unsigned int>(std::pow(NUMBER_OF_COLORS, NUMBER_OF_FIELDS));
  for (unsigned int guess_scalar = 0; guess_scalar < guess_scalar_max; guess_scalar++) {
    unsigned int remainder = guess_scalar;
    guess                  = {};

    for (unsigned int field = NUMBER_OF_FIELDS; (field != 0u) && (remainder != 0); field--) {
      unsigned int exponent    = static_cast<unsigned int>(std::pow(NUMBER_OF_COLORS, field - 1));
      unsigned int coefficient = remainder / exponent;
      remainder -= (coefficient == 0u ? 0u : coefficient * exponent);
      guess[field - 1] = static_cast<Color>(coefficient);
    }

    if (verbose) {
      helpers::print(guess);
    }

    if (helpers::win(game_.guess(guess))) {
      return guess_scalar + 1;
    }
  }

  return 0;
}
