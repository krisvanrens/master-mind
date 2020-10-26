#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace helpers {

void print(std::string&& prefix, const auto& series) {
  std::cout << prefix << ": [" << [&] {
    std::stringstream result;
    std::ranges::for_each(std::as_const(series), [&](const auto field) { result << static_cast<int>(field); });
    return result.str();
  }() << "]\n";
}

} // namespace helpers
