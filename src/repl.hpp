#pragma once
#include <string>
#include <vector>
#include <ostream>
#include "lisp.hpp"

class REPL {
public:
  REPL();
  std::string operator()(std::string);
private:
  Env env;
};
