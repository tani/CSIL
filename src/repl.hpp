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

int tokenize(std::string,std::vector<Symbol>&);
int parse(std::vector<Symbol>,ObjPtr);
ObjPtr eval(ObjPtr,Env);
void print(std::ostream&,ObjPtr);
void init(Env& global_env);
