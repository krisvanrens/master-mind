#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverNaive final : public Solver {
public:
  explicit SolverNaive(const MasterMind& game);

  [[nodiscard]] unsigned long solve(bool verbose) override;
};
