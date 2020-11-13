#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverOptimal final : public Solver {
public:
  explicit SolverOptimal(const MasterMind& game, bool verbose);

  [[nodiscard]] unsigned long solve() override;
};
