#include <docopt/docopt.h>

#include <iterator>
#include <utility>

#include "helpers.hpp"
#include "master-mind.hpp"

static constexpr auto USAGE =
  R"(Usage: master-mind-cli [-h|--help] [--secret=SECRET] [-v|--verbose] GUESS

-h --help       Show this help info
--secret=SECRET Provide a custom secret instead of generating a random one
-v --verbose    Show guess/secret/outcome
)";

int main(int argc, char** argv) {
  const auto args         = docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, true);
  const bool verbose      = args.at("-v") || args.at("--verbose");
  const bool customSecret = !!args.at("--secret");

  auto&& secret =
    (customSecret ? helpers::secretFromString(args.at("--secret").asString()) : helpers::generateRandomSecret());
  auto guess = helpers::secretFromString(args.at("GUESS").asString());
  auto score = MasterMind{std::move(secret)}.guess(guess);

  if (verbose) {
    helpers::print(secret);
    helpers::print(guess);
    helpers::print(score);
  }

  return (helpers::win(score) ? 0 : 1);
}
