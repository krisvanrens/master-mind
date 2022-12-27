#include "helpers.hpp"

#include <fmt/core.h>

#include <algorithm>
#include <charconv>
#include <random>
#include <ranges>
#include <sstream>
#include <string>
#include <system_error>

#include "master-mind.hpp"

[[nodiscard]] static Color char_to_color(char character) {
  unsigned int result;
  auto [_, ec] = std::from_chars(&character, &character + 1, result);
  if ((ec != std::errc{}) || (result >= NUMBER_OF_COLORS)) {
    throw std::runtime_error{fmt::format("Failed to convert character '{}' to color", character)};
  }

  return static_cast<Color>(result);
}

namespace helpers {

Secret generate_secret() {
  Secret result;

  std::random_device              device;
  std::mt19937                    generator(device());
  std::uniform_int_distribution<> distribution(0, NUMBER_OF_COLORS - 1);
  std::ranges::for_each(result, [&](auto& field) { field = static_cast<Color>(distribution(generator)); });

  return result;
}

Secret string_to_secret(const std::string& str) {
  Secret result{};
  auto   resultColor = result.begin();
  std::ranges::for_each_n(str.cbegin(), static_cast<long>(std::min(str.size(), result.size())),
                          [&](auto character) { *resultColor++ = char_to_color(character); });
  return result;
}

std::string to_string(const auto& series) {
  std::stringstream result;
  std::ranges::for_each(std::ranges::reverse_view{series}, [&](const auto field) { result << static_cast<int>(field); });
  return result.str();
}

static void print(std::string&& prefix, const auto& series) {
  fmt::print("{}: [{}]\n", prefix, to_string(series));
}

void print(const Score& score) {
  print("Score  ", score);
}

void print(const Secret& secret) {
  print("Secret ", secret);
}

} // namespace helpers
