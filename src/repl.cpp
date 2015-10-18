#include "repl.hpp"
#include <sstream>
REPL::REPL(Env env) : env(env){};
std::string REPL::operator()(std::string exp){
  std::vector<Symbol> tokens;
  std::stringstream result;
  ObjPtr obj = std::make_shared<Object>();
  tokenize(exp,tokens);
  parse(tokens,obj);
  obj = eval(obj,env);
  print(result,obj);
  return result.str();
}
