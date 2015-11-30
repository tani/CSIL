#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace function {
using namespace core;
class Cons {
public:
  core::ObjPtr operator()(core::ObjPtr exp) {
    auto val = car(exp);
    auto list = cadr(exp);
    return cons(val, list);
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
