#include "repl.hpp"
#include <sstream>

int tokenize(std::string,std::vector<Symbol>&);
int parse(std::vector<Symbol>,ObjPtr);
ObjPtr eval(ObjPtr,Env&);
void print(std::ostream&,ObjPtr);
void init();

REPL::REPL() {init();};
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
