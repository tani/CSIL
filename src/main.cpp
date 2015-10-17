#include "lisp.hpp"
#include <iostream>
#include <vector>
#include <string>

void init(Env &);
int tokenize(std::string, std::vector<std::string> &);
int parse(std::vector<std::string>::iterator, ObjPtr);
ObjPtr eval(ObjPtr, Env);
int print(ObjPtr);
int main(int argc, char const *argv[]) {
  Env global_env;
  init(global_env);
  std::string line;
  std::vector<std::string> tokens;
  ObjPtr obj;
  while (true) {
    getline(std::cin, line);
    tokenize(line, tokens);
    obj = std::make_shared<Object>();
    parse(tokens.begin(), obj);
    print(eval(obj, global_env));
    tokens.clear();
  }
  return 0;
}
