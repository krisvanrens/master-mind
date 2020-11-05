#pragma once

#include "../master-mind.hpp"

class Solver {
protected:
  const MasterMind& game_;

public:
  explicit Solver(const MasterMind& game);
  virtual ~Solver() = default;

  [[nodiscard]] virtual unsigned long solve(bool verbose) = 0;
};
