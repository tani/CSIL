#include "lisp.hpp"
#include "util.hpp"
#include <unordered_map>
ObjPtr eval(ObjPtr obj, Env env) {
  if (obj->type == Object::ATOM) {
    if (obj->atom.type == Atom::SYMBOL) {
      return env.variables.at(obj->atom.symbol);
    } else {
      return obj;
    }
  } else if (env.functions.count(car(obj)->atom.symbol) != 0) {
    for (auto a = cdr(obj); a != nullptr; a = cdr(a)) {
      a->cons.car = eval(car(a), env);
    }
    return env.functions.at(car(obj)->atom.symbol) ->atom.function(cdr(obj), env);
  } else if (env.macros.count(car(obj)->atom.symbol) != 0) {
    return eval(env.macros.at(car(obj)->atom.symbol)->atom.function(cdr(obj), env), env);
  } else if (env.forms.count(car(obj)->atom.symbol) != 0) {
    return env.forms.at(car(obj)->atom.symbol)->atom.function(cdr(obj), env);
  }
  return nullptr;
}
