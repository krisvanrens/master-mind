#pragma once

#include "../master-mind.hpp"

class MasterMindSolver {
public:
  virtual ~MasterMindSolver() = default;

  [[nodiscard]] virtual unsigned long solve() = 0;
};
