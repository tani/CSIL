#include "lisp.hpp"
#include "util.hpp"
#include <unordered_map>
namespace islisp {
namespace core {
extern std::unordered_map<Symbol, ObjPtr> builtin_macros;
extern std::unordered_map<Symbol, ObjPtr> builtin_functions;
extern std::unordered_map<Symbol, ObjPtr> builtin_forms;

ObjPtr eval(ObjPtr obj, Env &env) {
  if (obj->type == Object::ATOM) {
    if (obj->atom.type == Atom::SYMBOL) {
      return env.variables.at(obj->atom.symbol);
    } else {
      return obj;
    }
  } else {
    auto sym = car(obj)->atom.symbol;
    if (env.functions.count(sym) != 0) {
      for (auto a = cdr(obj); !(*a == *nil()); a = cdr(a)) {
        a->cons.car = eval(car(a), env);
      }
      return env.functions.at(sym)->atom.function(cdr(obj));
    } else if (env.macros.count(sym) != 0) {
      return eval(env.macros.at(sym)->atom.function(cdr(obj)), env);
    } else if (builtin_functions.count(sym) != 0) {
      for (auto a = cdr(obj); !(*a == *nil()); a = cdr(a)) {
        a->cons.car = eval(car(a), env);
      }
      return builtin_functions.at(sym)->atom.function(cdr(obj));
    } else if (builtin_macros.count(sym) != 0) {
      return eval(builtin_macros.at(sym)->atom.function(cdr(obj)), env);
    } else if (builtin_forms.count(sym) != 0) {
      return builtin_forms.at(sym)->atom.form(cdr(obj), env);
    }
  }
  return nil();
}
}
}
