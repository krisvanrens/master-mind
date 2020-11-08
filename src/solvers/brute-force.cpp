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
  auto generateNextGuess = []() -> std::pair<Secret, unsigned int> {
    Secret result{};

    static unsigned int guess_scalar = 0;
    unsigned int        remainder    = guess_scalar++;

    for (unsigned int field = NUMBER_OF_FIELDS; (field != 0u) && (remainder != 0); field--) {
      unsigned int exponent    = static_cast<unsigned int>(std::pow(NUMBER_OF_COLORS, field - 1));
      unsigned int coefficient = remainder / exponent;
      remainder -= (coefficient == 0u ? 0u : coefficient * exponent);
      result[field - 1] = static_cast<Color>(coefficient);
    }

    return {result, guess_scalar};
  };

  while (true) {
    auto [guess, number_of_tries] = generateNextGuess();

    if (verbose) {
      fmt::print("Trying guess #{}: {}..\n", number_of_tries, to_string(guess));
    }

    if (win(game_.guess(guess))) {
      return number_of_tries;
    }
  }
}
