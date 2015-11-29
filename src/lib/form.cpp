#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace core {
ObjPtr eval(ObjPtr, Environment &);
}
namespace form {
using namespace core;
class If {
public:
  ObjPtr operator()(ObjPtr exp,Environment& env) {
    auto test = car(exp);
    auto then = cadr(exp);
    auto otherwise = caddr(exp);
    if (eval(test, env) != nullptr) {
      return eval(then, env);
    }
    return eval(otherwise, env);
  }
};
class Define {
public:
  ObjPtr operator()(ObjPtr exp, Environment& env) {
    auto name = car(exp);
    auto value = eval(cadr(exp), env);
    if (value->type == Object::ATOM && value->atom.type == Atom::FUNCTION) {
      env.functions[name->atom.symbol] = value;
    } else {
      env.variables[name->atom.symbol] = value;
    }
    return name;
  }
};
class Quote {
public:
  ObjPtr operator()(ObjPtr exp, Environment& env) { return car(exp); }
};
class Apply {
public:
  ObjPtr operator()(ObjPtr exp, Environment& env) { return cadr(exp)->atom.function(caddr(exp)); }
};
class Lambda {
public:
  ObjPtr operator()(ObjPtr exp, Environment& env) {
    auto args = car(exp);
    auto body = cadr(exp);
    auto lambda = std::make_shared<Object>();
    createAtom(lambda, [=](ObjPtr vars) -> ObjPtr {
      ObjPtr result;
      auto closure = env;
      for (auto a = args, v = vars; v != nullptr && a != nullptr;
           a = cdr(a), v = cdr(v)) {
        if (car(a)->atom.symbol == "&rest") {
          closure.variables[cadr(a)->atom.symbol] = v;
          break;
        }
        closure.variables[car(a)->atom.symbol] = car(v);
      }
      for (auto b = body; b != nullptr; b = cdr(b)) {
        result = eval(car(b), closure);
      }
      return result;
    });
    return lambda;
  }
};
}
}
