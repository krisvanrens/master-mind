#include "naive.hpp"

#include <fmt/format.h>

#include <algorithm>
#include <vector>

#include "../helpers.hpp"
#include "../master-mind.hpp"

#define CHECK(secret)                \
  if (helpers::win(check(secret))) { \
    return number_of_tries_;         \
  }

SolverNaive::SolverNaive(const MasterMind& game, bool verbose)
  : Solver{game, verbose} {
}

unsigned long SolverNaive::solve() {
  using namespace std::ranges;

  std::vector<Color> colors;

  for (unsigned int color = 0u; color < NUMBER_OF_COLORS; color++) {
    Secret guess{};
    fill(guess, static_cast<Color>(color));

    CHECK(guess);

    for_each(game_.guess(guess), [&](auto field) {
      if (field == Outcome::Correct) {
        colors.push_back(static_cast<Color>(color));
      }
    });
  }

  if (colors.size() != NUMBER_OF_FIELDS) {
    throw std::runtime_error("Number of guessed colors does not correspond to the number of fields!");
  }

  Secret guess{};
  for_each(indices(guess), [&](auto field) { guess[field] = colors[field]; });

  CHECK(guess);

  const auto shiftRight = [](auto& secret) {
    Color first = secret[0];
    for (unsigned int field = 1; field < NUMBER_OF_FIELDS; field++) {
      secret[field - 1] = secret[field];
    }

    secret[NUMBER_OF_FIELDS - 1] = first;
  };

  const auto count_correct = [this](const auto& secret) {
    return count_if(game_.guess(secret), [](auto outcome) { return outcome == Outcome::Correct; });
  };

  auto best_guess          = guess;
  auto best_number_correct = count_correct(guess);
  for (auto shift = 0u; shift < (NUMBER_OF_FIELDS - 1); shift++) {
    shiftRight(guess);

    CHECK(guess);

    auto number_correct = count_correct(guess);
    if (number_correct > best_number_correct) {
      best_guess          = guess;
      best_number_correct = number_correct;
    }
  }

  CHECK(best_guess);

  // TODO: Find the solution!

  return number_of_tries_;
}
