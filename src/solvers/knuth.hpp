#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverKnuth final : public Solver {
public:
  explicit SolverKnuth(const MasterMind& game, bool verbose);

  [[nodiscard]] unsigned long solve() override;
};
