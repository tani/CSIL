#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/repl.hpp"

TEST_CASE("EQ_TEST","[eq cons]")
{
  REPL repl;
  REQUIRE("t" == repl("(eq 1 1)"));
  REQUIRE("t" == repl("(eq (cons 1 1) (cons 1 1))"));
  REQUIRE("nil" == repl("(eq 2 1)"));
  REQUIRE("nil" == repl("(eq (cons 1 2) (cons 1 1))"));
}
