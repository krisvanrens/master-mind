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

[[nodiscard]] static Secret generateRandomSecret() {
  Secret result;

  std::random_device              device;
  std::mt19937                    generator(device());
  std::uniform_int_distribution<> distribution(0, NUMBER_OF_COLORS - 1);
  std::ranges::for_each(result, [&](auto& field) { field = static_cast<Color>(distribution(generator)); });

  return result;
}

[[nodiscard]] static Secret secretFromString(const std::string& secret) {
  Secret result;
  auto   resultColor = result.begin();

  std::ranges::for_each_n(secret.cbegin(), static_cast<long>(std::min(secret.size(), result.size())),
                          [&](auto character) {
                            unsigned int color = static_cast<unsigned int>(std::atoi(&character));
                            *resultColor++     = static_cast<Color>(std::clamp(color, 0u, NUMBER_OF_COLORS - 1));
                          });

  return result;
}

static constexpr auto USAGE =
  R"(Usage: master-mind-cli [-h|--help] [--secret=SECRET] [-v|--verbose] GUESS

-h --help       Show this help info
--secret=SECRET Provide a custom secret instead of generating a random one
-v --verbose    Show guess/secret/outcome
)";

int main(int argc, char** argv) {
  const auto args         = docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, true);
  const bool verbose      = (args.find("-v") != args.end()) || (args.find("--verbose") != args.end());
  const bool customSecret = (args.find("--secret") != args.end()) && args.at("--secret");

  auto&& secret = (customSecret ? secretFromString(args.at("--secret").asString()) : generateRandomSecret());
  auto   guess  = secretFromString(args.at("GUESS").asString());
  auto   score  = MasterMind{std::move(secret)}.guess(guess);

  if (verbose) {
    print(secret);
    print(guess);
    print(score);
  }

  return (win(score) ? 0 : 1);
}
