#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <numeric>
#include <sstream>
#include <utility>

static constexpr unsigned int NUMBER_OF_FIELDS = 100;
static constexpr unsigned int NUMBER_OF_COLORS = 10;

enum struct Color : unsigned char {
  Black = 0,
  White,
  Blue,
  Green,
  Yellow,
  Orange,
  Red,
  Purple,
  Brown,
  Grey,
  MAX_NUMBER_OF_COLORS_
};

static_assert(NUMBER_OF_FIELDS > 0);
static_assert(NUMBER_OF_COLORS > 0);
static_assert(NUMBER_OF_COLORS <= static_cast<unsigned char>(Color::MAX_NUMBER_OF_COLORS_));

enum struct Outcome : unsigned char {
  Incorrect = 0,
  CorrectColor,
  Correct
};

template<typename T>
using Container = typename std::array<T, NUMBER_OF_FIELDS>;

using Secret = Container<Color>;
using Score = Container<Outcome>;
using Indices = Container<unsigned int>;

namespace helpers {

void print(std::string prefix, const auto &series) {
  std::cout << prefix << ": [" << [&]{
    std::stringstream result;
    std::ranges::for_each(std::as_const(series), [&](const auto field) { result << static_cast<int>(field); });
    return result.str();
  }() << "]\n";
}

} // namespace helpers

template<typename T>
[[nodiscard]] constexpr auto indices(T) {
  Indices result;
  std::iota(result.begin(), result.end(), 0);
  return result;
}

[[nodiscard]] constexpr bool win(const Score &score) {
  return std::ranges::all_of(score, [](const auto &field) { return field == Outcome::Correct; });
}

void print(const Secret &secret) {
  helpers::print("Secret", secret);
}

void print(const Score &score) {
  helpers::print("Score ", score);
}

[[nodiscard]] Secret generateSecret() {
  Secret result;

  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<> distribution(0, NUMBER_OF_COLORS - 1);
  std::ranges::for_each(result, [&](auto &field) { field = static_cast<Color>(distribution(generator)); });

  return result;
}

class MasterMind {
private:
  using IntermediateScore = std::pair<Score, Container<bool>>;

  Secret secret_ = {};

  [[nodiscard]] constexpr IntermediateScore scoreFullyCorrectGuesses(const Secret& secret) const {
    Score result = {};
    Container<bool> marker = {};
  
    std::ranges::for_each(indices(secret), [&](auto index) {
      if (secret[index] == secret_[index]) {
        result[index] = Outcome::Correct;
        marker[index] = true;
      }
    });
  
    return {result, marker};
  }

  [[nodiscard]] constexpr Score scoreColorCorrectGuesses(const Secret& secret, IntermediateScore&& score) const {
    auto&& [result, marker] = std::move(score);
  
    std::ranges::for_each(indices(secret), [&](auto index) {
      if (result[index] != Outcome::Correct) {
        std::ranges::any_of(indices(secret), [&](auto markerIndex) {
          if (!marker[markerIndex] && (secret[index] == secret_[markerIndex])) {
            result[index] = Outcome::CorrectColor;
            marker[markerIndex] = true;
            return true;
          }
  
          return false;
        });
      }
    });
  
    return result;
  }

public:
  MasterMind()
    : secret_{generateSecret()} {
    print(secret_);
  }

  [[nodiscard]] constexpr Score guess(const Secret& secret) const {
    auto result = scoreColorCorrectGuesses(secret, scoreFullyCorrectGuesses(secret));
    std::ranges::sort(result, [](auto a, auto b) { return static_cast<int>(a) > static_cast<int>(b); });
    return result;
  }
};

int main() {
  auto guess = generateSecret();
  auto score = MasterMind{}.guess(guess);

  print(guess);
  print(score);

  return win(score);
}
