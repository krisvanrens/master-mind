#include <docopt/docopt.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iterator>
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

[[nodiscard]] static Secret generateRandomSecret(bool verbose = false) {
  Secret result;

  std::random_device              device;
  std::mt19937                    generator(device());
  std::uniform_int_distribution<> distribution(0, NUMBER_OF_COLORS - 1);
  std::ranges::for_each(result, [&](auto& field) { field = static_cast<Color>(distribution(generator)); });

  if (verbose) {
    print(result);
  }

  return result;
}

[[nodiscard]] static Secret secretFromString(const std::string& secret) {
  Secret result;
  auto   resultColor = result.begin();

  std::ranges::for_each_n(secret.cbegin(), static_cast<long>(std::min(secret.size(), result.size())), [&](auto color) {
    *resultColor++ =
      static_cast<Color>(std::clamp(std::atoi(&color), 0, static_cast<int>(Color::MAX_NUMBER_OF_COLORS_) - 1));
  });

  return result;
}

static constexpr auto USAGE =
  R"(Usage: master-mind-cli [-h|--help] [-v|--verbose] <guess>

-h --help    Show this help info
-v --verbose Show guess/secret/outcome
)";

int main(int argc, char** argv) {
  const auto arguments = docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, true);
  const bool verbose   = (arguments.find("-v") != arguments.end()) || (arguments.find("--verbose") != arguments.end());

  auto&& secret = generateRandomSecret(verbose);
  auto   guess  = secretFromString(arguments.at("<guess>").asString());
  auto   score  = MasterMind{std::move(secret)}.guess(guess);

  if (verbose) {
    print(guess);
    print(score);
  }

  return (win(score) ? 0 : 1);
}
