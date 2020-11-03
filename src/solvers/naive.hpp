#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverNaive final : public MasterMindSolver {
private:
  const MasterMind game_;

public:
  SolverNaive(const MasterMind& game);

  [[nodiscard]] unsigned long solve() override;
};
