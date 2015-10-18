#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/repl.hpp"

TEST_CASE("Test","[sample]")
{
  REPL repl;
  REQUIRE("(1 . 2)" == repl("(cons 1 2)"));
}
