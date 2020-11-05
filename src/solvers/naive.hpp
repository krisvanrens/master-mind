#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverNaive final : public Solver {
private:
  const MasterMind game_;

public:
  SolverNaive(const MasterMind& game);

  [[nodiscard]] unsigned long solve(bool verbose) override;
};
