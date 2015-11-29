#include "repl.hpp"
#include <sstream>

namespace islisp {
namespace core {
ObjPtr eval(ObjPtr, Env &);
void init();
}
namespace io {
using namespace core;
int tokenize(std::string, std::vector<Symbol> &);
int parse(std::vector<Symbol>, ObjPtr);
void print(std::ostream &, ObjPtr);
}
}
using namespace islisp::core;
using namespace islisp::io;

REPL::REPL() { init(); };
std::string REPL::operator()(std::string exp) {
  std::vector<Symbol> tokens;
  std::stringstream result;
  ObjPtr obj = std::make_shared<Object>();
  tokenize(exp, tokens);
  parse(tokens, obj);
  obj = eval(obj, env);
  print(result, obj);
  return result.str();
}
