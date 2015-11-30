#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace core {
ObjPtr eval(ObjPtr,Environment&);
}
namespace form {
using namespace core;
class Lambda {
public:
  ObjPtr operator()(ObjPtr exp, Environment& env) {
    auto args = car(exp);
    auto body = cadr(exp);
    auto lambda = std::make_shared<Object>();
    createAtom(lambda, [=](ObjPtr vars) -> ObjPtr {
      ObjPtr result;
      auto closure = env;
      for (auto a = args, v = vars; v != nil() && a != nil();
           a = cdr(a), v = cdr(v)) {
        if (car(a)->atom.symbol == "&rest") {
          closure.variables[cadr(a)->atom.symbol] = v;
          break;
        }
        closure.variables[car(a)->atom.symbol] = car(v);
      }
      for (auto b = body; b != nil(); b = cdr(b)) {
        result = eval(car(b), closure);
      }
      return result;
    });
    return lambda;
  }
};
}
}
