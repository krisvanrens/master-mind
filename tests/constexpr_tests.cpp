#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../source/helpers.hpp"
#include "../source/master-mind.hpp"

#ifdef TEST_NONSTATIC_REQUIRE
#define STATIC_REQUIRE(assertion) REQUIRE(assertion)
#else
#define STATIC_REQUIRE(assertion) static_assert(assertion, #assertion)
#endif

TEST_SUITE("MasterMind") {
  TEST_CASE("Construction") {
    SUBCASE("Default secret") {
      constexpr MasterMind mm{Secret{}};
      STATIC_REQUIRE(helpers::win(mm.guess(Secret{})));
    }

    SUBCASE("Non-default secret") {
      constexpr Secret     s = {Color::White};
      constexpr MasterMind mm{Secret{s}};
      STATIC_REQUIRE(helpers::win(mm.guess(Secret{s})));
    }
  }
} // TEST_SUITE
