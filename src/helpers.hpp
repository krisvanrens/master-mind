#pragma once

#include <algorithm>
#include <string>

#include "master-mind.hpp"

namespace helpers {

[[nodiscard]] Secret generateRandomSecret();
[[nodiscard]] Secret secretFromString(const std::string& secret);

void print(const Score& score);
void print(const Secret& secret);

[[nodiscard]] static constexpr bool win(const Score& score) {
  return std::ranges::all_of(score, [](const auto& field) { return field == Outcome::Correct; });
}

} // namespace helpers
