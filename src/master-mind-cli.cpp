#include <algorithm>
#include <array>
#include <numeric>
#include <random>
#include <utility>

#include "helpers.hpp"
#include "master-mind.hpp"


[[nodiscard]] static constexpr bool win(const Score& score) {
  return std::ranges::all_of(score, [](const auto& field) { return field == Outcome::Correct; });
}

static void print(const Secret& secret) {
  helpers::print("Secret", secret);
}

static void print(const Score& score) {
  helpers::print("Score ", score);
}

[[nodiscard]] static Secret generateSecret() {
  Secret result;

  std::random_device              device;
  std::mt19937                    generator(device());
  std::uniform_int_distribution<> distribution(0, NUMBER_OF_COLORS - 1);
  std::ranges::for_each(result, [&](auto& field) { field = static_cast<Color>(distribution(generator)); });

  return result;
}

int main() {
  auto guess = generateSecret();
  auto score = MasterMind{generateSecret()}.guess(guess);

  print(guess);
  print(score);

  return win(score);
}
