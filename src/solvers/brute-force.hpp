#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverBruteForce final : public MasterMindSolver {
private:
  const MasterMind game_;

public:
  SolverBruteForce(const MasterMind& game);

  [[nodiscard]] unsigned long solve() override;
};
