#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace function {
using namespace core;
class Cons {
public:
  core::ObjPtr operator()(core::ObjPtr exp) {
    auto val = core::car(exp);
    auto list = core::cadr(exp);
    return core::cons(val, list);
  }
};
class Car {
public:
  ObjPtr operator()(ObjPtr exp) { return car(car(exp)); }
};
class Cdr {
public:
  ObjPtr operator()(ObjPtr exp) { return cdr(car(exp)); }
};
}
}
