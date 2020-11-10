#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverNaive final : public Solver {
public:
  explicit SolverNaive(const MasterMind& game, bool verbose);

  [[nodiscard]] unsigned long solve() override;
};
