#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <utility>

#include "../source/helpers.hpp"
#include "../source/master-mind.hpp"

TEST_SUITE("MasterMind") {
  TEST_CASE("Construction") {
    SUBCASE("Default secret") {
      MasterMind mm{Secret{}};
      CHECK(helpers::win(mm.guess(Secret{})));
    }

    SUBCASE("Non-default secret") {
      constexpr Secret s = {Color::White};

      MasterMind mm{Secret{s}};
      CHECK(helpers::win(mm.guess(Secret{s})));
    }
  }

  TEST_CASE("Copy construction") {
    constexpr Secret s = {Color::White};

    MasterMind mm1{Secret{s}};

    REQUIRE(helpers::win(mm1.guess(Secret{s})));

    MasterMind mm2{mm1};

    CHECK(helpers::win(mm2.guess(Secret{s})));
  }

  TEST_CASE("Move construction") {
    constexpr Secret s = {Color::White};

    MasterMind mm1{Secret{s}};

    REQUIRE(helpers::win(mm1.guess(Secret{s})));

    MasterMind mm2{std::move(mm1)};

    CHECK(helpers::win(mm2.guess(Secret{s})));
  }

  TEST_CASE("Copy assignment") {
    constexpr Secret s = {Color::White};

    MasterMind mm1{Secret{s}};
    MasterMind mm2{Secret{}};

    REQUIRE(helpers::win(mm2.guess(Secret{})));
    REQUIRE(helpers::win(mm1.guess(Secret{s})));

    mm2 = mm1;


    CHECK(helpers::win(mm2.guess(Secret{s})));
  }

  TEST_CASE("Move assignment") {
    constexpr Secret s = {Color::White};

    MasterMind mm1{Secret{s}};
    MasterMind mm2{Secret{}};

    REQUIRE(helpers::win(mm2.guess(Secret{})));
    REQUIRE(helpers::win(mm1.guess(Secret{s})));

    mm2 = std::move(mm1);

    CHECK(helpers::win(mm2.guess(Secret{s})));
  }
} // TEST_SUITE
