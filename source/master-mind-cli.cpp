#include <docopt/docopt.h>

#include <iterator>
#include <utility>

#include "helpers.hpp"
#include "master-mind.hpp"

using namespace helpers;

static constexpr auto USAGE =
  R"(Usage: master-mind-cli [-h|--help] [--secret=SECRET] [-v|--verbose] GUESS

-h --help       Show this help info
--secret=SECRET Provide a custom secret instead of generating a random one
-v --verbose    Show guess/secret/outcome)";

int main(int argc, char** argv) {
  const auto args          = docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, true);
  auto       verbose       = args.at("-v").asBool() || args.at("--verbose").asBool();
  auto       custom_secret = args.at("--secret");

  auto&& secret = (custom_secret ? string_to_secret(custom_secret.asString()) : generate_secret());
  auto   guess  = string_to_secret(args.at("GUESS").asString());
  auto   score  = MasterMind{std::move(secret)}.guess(guess);

  if (verbose) {
    print(secret);
    print(guess);
    print(score);
  }

  return (win(score) ? 0 : 1);
}
