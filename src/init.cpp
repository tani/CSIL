#include "util.hpp"
#include "lisp.hpp"
#include "lib/define.cpp"
#include "lib/cons.cpp"
#include "lib/equal.cpp"
#include "lib/atom.cpp"
#include "lib/form.cpp"
#include <unordered_map>

namespace islisp {
namespace core {
std::unordered_map<Symbol, ObjPtr> builtin_macros;
std::unordered_map<Symbol, ObjPtr> builtin_functions;
std::unordered_map<Symbol, ObjPtr> builtin_forms;
inline void defmacro(std::string name, Function macro) {
  builtin_macros[name] = createAtom(std::make_shared<Object>(), macro);
}
inline void defun(std::string name, Function function) {
  builtin_functions[name] = createAtom(std::make_shared<Object>(), function);
}
inline void deform(std::string name, Form form) {
  builtin_forms[name] = createAtom(std::make_shared<Object>(), form);
}
void init() {
  defmacro("defun", macro::Defun());
  defmacro("defvar", macro::Defvar());
  defun("cons", function::Cons());
  defun("car", function::Car());
  defun("cdr", function::Cdr());
  defun("atom", function::Atom());
  defun("eq", function::Eq());
  deform("if", form::If());
  deform("define", form::Define());
  deform("quote", form::Quote());
  deform("lambda", form::Lambda());
  deform("apply", form::Apply());
}
}
}
