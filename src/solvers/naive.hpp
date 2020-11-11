#pragma once

#include <vector>

#include "../master-mind.hpp"
#include "solver.hpp"

class SolverNaive final : public Solver {
private:
  using Colors = std::vector<Color>;

  void   check_with_exception(Secret secret);
  Colors solve_colors();
  Secret guess_from_colors(Colors&& colors);
  Secret find_best_shift(Secret&& secret);
  Secret find_best_swap(Secret&& guess);

public:
  explicit SolverNaive(const MasterMind& game, bool verbose);

  [[nodiscard]] unsigned long solve() override;
};
