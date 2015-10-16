#include "lisp.hpp"
#include <iostream>
#include <vector>
#include <string>

void init();
int tokenize(std::string, std::vector<std::string> &);
int parse(std::vector<std::string>::iterator, ObjPtr);
ObjPtr eval(ObjPtr);
int print(ObjPtr);
int main(int argc, char const *argv[]) {
  init();
  std::string line;
  std::vector<std::string> tokens;
  ObjPtr obj;
  while (true) {
    getline(std::cin, line);
    tokenize(line, tokens);
    obj = std::make_shared<Object>();
    parse(tokens.begin(), obj);
    print(eval(obj));
    tokens.clear();
  }
  return 0;
}
