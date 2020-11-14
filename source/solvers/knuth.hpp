#pragma once

#include <vector>

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverKnuth final : public Solver {
private:
  std::vector<Secret> codes_;

  void initialize_set();

public:
  explicit SolverKnuth(const MasterMind& game, bool verbose);

  [[nodiscard]] unsigned long solve() override;
};
