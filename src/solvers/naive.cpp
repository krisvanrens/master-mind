#include "naive.hpp"

#include <fmt/format.h>

#include <algorithm>
#include <stdexcept>

#include "../helpers.hpp"
#include "../master-mind.hpp"

using namespace std::ranges;

void SolverNaive::check_with_exception(Secret secret) {
  if (helpers::win(check(secret))) {
    throw true;
  }
}

SolverNaive::Colors SolverNaive::solve_colors() {
  Colors colors;

  for (unsigned int color = 0u; color < NUMBER_OF_COLORS; color++) {
    Secret guess{};
    fill(guess, static_cast<Color>(color));

    check_with_exception(guess);

    for_each(game_.guess(guess), [&](auto field) {
      if (field == Outcome::Correct) {
        colors.push_back(static_cast<Color>(color));
      }
    });
  }

  if (colors.size() != NUMBER_OF_FIELDS) {
    throw std::runtime_error("Number of guessed colors does not correspond to the number of fields!");
  }

  return colors;
}

Secret SolverNaive::guess_from_colors(Colors&& colors) {
  Secret guess{};
  for_each(indices(guess), [&](auto field) { guess[field] = colors[field]; });

  return guess;
}

Secret SolverNaive::find_best_shift(Secret&& guess) {
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

  check_with_exception(guess);

  auto best_guess          = guess;
  auto best_number_correct = count_correct(guess);
  for (auto shift = 0u; shift < (NUMBER_OF_FIELDS - 1); shift++) {
    shiftRight(guess);

    check_with_exception(guess);

    auto number_correct = count_correct(guess);
    if (number_correct > best_number_correct) {
      best_guess          = guess;
      best_number_correct = number_correct;
    }
  }

  return best_guess;
}

Secret SolverNaive::find_best_swap(Secret&& guess) {
  const auto count_correct = [this](const auto& secret) {
    return count_if(game_.guess(secret), [](auto outcome) { return outcome == Outcome::Correct; });
  };

  auto best_guess          = guess;
  auto best_number_correct = count_correct(guess);

  while (true) {
    for (auto source_field = 0u; source_field < (NUMBER_OF_FIELDS - 1); source_field++) {
      auto guess_initial = best_guess;

      for (auto dest_field = source_field + 1; dest_field < NUMBER_OF_FIELDS; dest_field++) {
        auto guess_swapped = guess_initial;

        std::swap(guess_swapped[source_field], guess_swapped[dest_field]);

        check_with_exception(guess_swapped);

        auto number_correct = count_correct(guess_swapped);
        if (number_correct > best_number_correct) {
          best_guess          = guess_swapped;
          best_number_correct = number_correct;
        }
      }
    }
  }

  return best_guess;
}

SolverNaive::SolverNaive(const MasterMind& game, bool verbose)
  : Solver{game, verbose} {
}

unsigned long SolverNaive::solve() {
  try {
    auto guess = find_best_swap(find_best_shift(guess_from_colors(solve_colors())));

    helpers::print(guess);
    helpers::print(game_.guess(guess));
  } catch (...) {
  }

  return number_of_tries_;
}
