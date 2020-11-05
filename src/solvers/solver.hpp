#pragma once

#include "../master-mind.hpp"

class Solver {
public:
  virtual ~Solver() = default;

  [[nodiscard]] virtual unsigned long solve(bool verbose) = 0;
};
