#include "knuth.hpp"

#include <fmt/format.h>

#include <cmath>

#include "../helpers.hpp"
#include "../master-mind.hpp"

void SolverKnuth::initialize_set() {
  auto guess_scalar = 0ul;

  for (auto& code : codes_) {
    auto remainder = guess_scalar++;

    for (unsigned int field = NUMBER_OF_FIELDS; (field != 0u) && (remainder != 0); field--) {
      auto exponent    = static_cast<unsigned long>(std::pow(NUMBER_OF_COLORS, field - 1));
      auto coefficient = remainder / exponent;
      remainder -= (coefficient == 0ul ? 0ul : coefficient * exponent);
      code[field - 1] = static_cast<Color>(coefficient);
    }
  }
}

SolverKnuth::SolverKnuth(const MasterMind& game, bool verbose)
  : Solver{game, verbose} {
  auto number_of_codes = static_cast<std::size_t>(std::pow(NUMBER_OF_COLORS, NUMBER_OF_FIELDS));
  codes_.reserve(number_of_codes);
  codes_.resize(number_of_codes);
}

/**
 * In 1977, Donald Knuth demonstrated that the codebreaker can solve the pattern in five moves or fewer, using an
 * algorithm that progressively reduces the number of possible patterns.[11] The algorithm works as follows:
 *
 * 1. Create the set S of 1296 possible codes (1111, 1112 ... 6665, 6666)
 *
 * 2. Start with initial guess 1122 (Knuth gives examples showing that other first guesses such as 1123, 1234 do not win
 * in five tries on every code)
 *
 * 3. Play the guess to get a response of coloured and white pegs.
 *
 * 4. If the response is four colored pegs, the game is won, the algorithm terminates.
 *
 * 5. Otherwise, remove from S any code that would not give the same response if it (the guess) were the code.
 *
 * 6. Apply minimax technique to find a next guess as follows: For each possible guess, that is, any unused code of the
 * 1296 not just those in S, calculate how many possibilities in S would be eliminated for each possible colored/white
 * peg score. The score of a guess is the minimum number of possibilities it might eliminate from S. A single pass
 * through S for each unused code of the 1296 will provide a hit count for each coloured/white peg score found; the
 * coloured/white peg score with the highest hit count will eliminate the fewest possibilities; calculate the score of a
 * guess by using "minimum eliminated" = "count of elements in S" - (minus) "highest hit count". From the set of guesses
 * with the maximum score, select one as the next guess, choosing a member of S whenever possible. (Knuth follows the
 * convention of choosing the guess with the least numeric value e.g. 2345 is lower than 3456. Knuth also gives an
 * example showing that in some cases no member of S will be among the highest scoring guesses and thus the guess cannot
 * win on the next turn, yet will be necessary to assure a win in five.)
 *
 * 7. Repeat from step 3.
 */
unsigned long SolverKnuth::solve() {
  initialize_set();

  // TODO

  return number_of_tries_;
}
