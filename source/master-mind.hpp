#pragma once

#include <algorithm>
#include <array>
#include <numeric>
#include <random>
#include <stdexcept>
#include <tuple>
#include <utility>

using namespace std::ranges;

static constexpr unsigned int NUMBER_OF_FIELDS = 16;
static constexpr unsigned int NUMBER_OF_COLORS = 10;

enum struct Color : unsigned char { Black = 0, White, Blue, Green, Yellow, Orange, Red, Purple, Brown, Grey, MAX_NUMBER_OF_COLORS_ };

static_assert(NUMBER_OF_FIELDS > 0);
static_assert(NUMBER_OF_COLORS > 0);
static_assert(NUMBER_OF_COLORS <= static_cast<unsigned char>(Color::MAX_NUMBER_OF_COLORS_));

enum struct Outcome : unsigned char { Incorrect = 0, CorrectColor, Correct };

template<typename T>
using Container = typename std::array<T, NUMBER_OF_FIELDS>;

using Secret  = Container<Color>;
using Score   = Container<Outcome>;
using Indices = Container<unsigned int>;

template<typename T>
[[nodiscard]] constexpr auto indices(T) {
  Indices result;
  std::iota(result.begin(), result.end(), 0);
  return result;
}

class MasterMind {
private:
  using IntermediateScore = std::pair<Score, Container<bool>>;

  Secret secret_ = {};

  [[nodiscard]] constexpr IntermediateScore scoreFullyCorrectGuesses(const Secret& secret) const;
  [[nodiscard]] constexpr Score             scoreColorCorrectGuesses(const Secret& secret, IntermediateScore&& score) const;

public:
  explicit constexpr MasterMind(Secret&& secret);

  [[nodiscard]] constexpr Score guess(const Secret& secret) const;
};

constexpr MasterMind::IntermediateScore MasterMind::scoreFullyCorrectGuesses(const Secret& secret) const {
  Score           result = {};
  Container<bool> marker = {};

  for_each(indices(secret), [&](auto index) {
    if (secret[index] == secret_[index]) {
      result[index] = Outcome::Correct;
      marker[index] = true;
    }
  });

  return {result, marker};
}

constexpr Score MasterMind::scoreColorCorrectGuesses(const Secret& secret, MasterMind::IntermediateScore&& score) const {
  auto&& [result, marker] = std::move(score);

  for_each(indices(secret), [&](auto index) {
    if (result[index] != Outcome::Correct) {
      any_of(indices(secret), [&](auto markerIndex) {
        if (!marker[markerIndex] && (secret[index] == secret_[markerIndex])) {
          result[index]       = Outcome::CorrectColor;
          marker[markerIndex] = true;
          return true;
        }

        return false;
      });
    }
  });

  return result;
}

constexpr MasterMind::MasterMind(Secret&& secret)
  : secret_{std::move(secret)} {
  if (any_of(secret_, [](auto value) { return value > static_cast<Color>(NUMBER_OF_COLORS); })) {
    throw std::runtime_error{"Secret contains unsupported colors"};
  }
}

constexpr Score MasterMind::guess(const Secret& secret) const {
  auto result = scoreColorCorrectGuesses(secret, scoreFullyCorrectGuesses(secret));
  sort(result, [](auto a, auto b) { return static_cast<int>(a) > static_cast<int>(b); });
  return result;
}
