#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverBruteForce final : public Solver {
public:
  explicit SolverBruteForce(const MasterMind& game, bool verbose);

  [[nodiscard]] unsigned long solve() override;
};
