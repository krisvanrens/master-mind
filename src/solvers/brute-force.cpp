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
  const auto generate_next_guess = []() -> std::pair<Secret, unsigned int> {
    const auto scalar_to_guess = [](unsigned long scalar) {
      Secret        result{};
      unsigned long remainder = scalar;

      for (unsigned int field = NUMBER_OF_FIELDS; (field != 0u) && (remainder != 0); field--) {
        unsigned long exponent    = static_cast<unsigned long>(std::pow(NUMBER_OF_COLORS, field - 1));
        unsigned long coefficient = remainder / exponent;
        remainder -= (coefficient == 0ul ? 0ul : coefficient * exponent);
        result[field - 1] = static_cast<Color>(coefficient);
      }

      return result;
    };

    static unsigned long guess_scalar = 0ul;
    return {scalar_to_guess(guess_scalar++), guess_scalar};
  };

  while (true) {
    const auto [guess, number_of_tries] = generate_next_guess();

    if (verbose) {
      fmt::print("Trying guess #{}: {}..\n", number_of_tries, to_string(guess));
    }

    if (win(game_.guess(guess))) {
      return number_of_tries;
    }
  }
}
