#include "lisp.hpp"
#include "repl.hpp"
#include <iostream>
#include <string>

void init(Env &);
ObjPtr eval(ObjPtr, Env);
int main(int argc, char const *argv[]) {
  Env global_env;
  init(global_env);
  REPL repl(global_env);
  std::string line;
  while (true) {
    getline(std::cin, line);
    std::cout<<repl(line)<<std::endl;
  }
  return 0;
}
