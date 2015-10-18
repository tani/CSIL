#include "../src/repl.hpp"
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(cisltest)
BOOST_AUTO_TEST_CASE(parser)
{
  REPL repl;
  BOOST_CHECK(std::string("(1 . (2 . (3 . nil)))") == repl("(quote (1 2 3))"));
}
BOOST_AUTO_TEST_CASE(defun)
{
  REPL repl;
  BOOST_CHECK(std::string("cons2") == repl("(defun cons2 (x y) (cons x y))"));
  BOOST_CHECK(std::string("(1 . 2)") == repl("(cons 1 2)"));
}

BOOST_AUTO_TEST_CASE(lambda)
{
  REPL repl;
  BOOST_CHECK(std::string("(1 . 2)") == repl("(apply (lambda (x y) (cons x y)) (quote (1 2)))"));
}
BOOST_AUTO_TEST_SUITE_END()
