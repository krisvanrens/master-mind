#pragma once

#include <vector>

#include "../master-mind.hpp"
#include "solver.hpp"

using Colors = std::vector<Color>;

class SolverNaive final : public Solver {
private:
  void   check_with_exception(Secret secret);
  Colors solve_colors();
  Secret find_best_shift(Secret&& guess);
  Secret find_best_swap(Secret&& guess);

public:
  explicit SolverNaive(const MasterMind& game, bool verbose);

  [[nodiscard]] unsigned long solve() override;
};
