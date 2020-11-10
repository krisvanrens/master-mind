#pragma once

#include "../master-mind.hpp"

class Solver {
protected:
  const MasterMind& game_;
  const bool        verbose_         = false;
  unsigned long     number_of_tries_ = 0ul;

  [[nodiscard]] Score check(const Secret& secret);

public:
  explicit Solver(const MasterMind& game, bool verbose);
  virtual ~Solver() = default;

  [[nodiscard]] virtual unsigned long solve() = 0;
};
