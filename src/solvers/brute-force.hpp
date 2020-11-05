#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverBruteForce final : public Solver {
private:
  const MasterMind game_;

public:
  SolverBruteForce(const MasterMind& game);

  [[nodiscard]] unsigned long solve(bool verbose) override;
};
