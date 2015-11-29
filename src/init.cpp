#include "util.hpp"
#include "lisp.hpp"
#include "lib/define.cpp"
#include "lib/cons.cpp"
#include "lib/equal.cpp"
#include "lib/atom.cpp"

#include <unordered_map>
namespace islisp {
namespace core {
std::unordered_map<Symbol, ObjPtr> buildin_macros;
std::unordered_map<Symbol, ObjPtr> buildin_functions;
inline void defmacro(std::string name, Function macro) {
  buildin_macros[name] = createAtom(std::make_shared<Object>(), macro);
}
inline void defun(std::string name, Function function) {
  buildin_functions[name] = createAtom(std::make_shared<Object>(), function);
}
void init() {
  defmacro("defun", macro::Defun());
  defmacro("defvar", macro::Defvar());
  defun("cons", function::Cons());
  defun("car", function::Car());
  defun("cdr", function::Cdr());
  defun("atom", function::Atom());
  defun("eq", function::Eq());
}
}
}
