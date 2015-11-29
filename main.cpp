#include "src/lisp.hpp"
#include "src/repl.hpp"
#include <iostream>
#include <string>
namespace islisp {
namespace core {
ObjPtr eval(ObjPtr, Env);
}
}
int main(int argc, char const *argv[]) {
  REPL repl;
  std::string line;
  while (true) {
    getline(std::cin, line);
    std::cout<<repl(line)<<std::endl;
  }
  return 0;
}
