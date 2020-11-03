#include "helpers.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "master-mind.hpp"

namespace helpers {

Secret generateRandomSecret() {
  Secret result;

  std::random_device              device;
  std::mt19937                    generator(device());
  std::uniform_int_distribution<> distribution(0, NUMBER_OF_COLORS - 1);
  std::ranges::for_each(result, [&](auto& field) { field = static_cast<Color>(distribution(generator)); });

  return result;
}

Secret secretFromString(const std::string& secret) {
  Secret result;
  auto   resultColor = result.begin();

  std::ranges::for_each_n(secret.cbegin(), static_cast<long>(std::min(secret.size(), result.size())),
                          [&](auto character) {
                            unsigned int color = static_cast<unsigned int>(std::atoi(&character));
                            *resultColor++     = static_cast<Color>(std::clamp(color, 0u, NUMBER_OF_COLORS - 1));
                          });

  return result;
}

static void print(std::string&& prefix, const auto& series) {
  std::cout << prefix << ": [" << [&] {
    std::stringstream result;
    std::ranges::for_each(std::as_const(series), [&](const auto field) { result << static_cast<int>(field); });
    return result.str();
  }() << "]\n";
}

void print(const Score& score) {
  print("Score  ", score);
}

void print(const Secret& secret) {
  print("Secret ", secret);
}

}
