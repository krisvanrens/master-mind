#pragma once

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverBruteForce final : public Solver {
public:
  explicit SolverBruteForce(const MasterMind& game);

  [[nodiscard]] unsigned long solve(bool verbose) override;
};
