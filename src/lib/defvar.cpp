#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace macro {
using namespace core;
class Defvar {
public:
  ObjPtr operator()(ObjPtr exp) {
    auto name = car(exp);
    auto var = cadr(exp);
    auto define = std::make_shared<Object>();
    createAtom(define, "define");
    return cons(define, cons(name, cons(var, nullptr)));
  }
};
}
}
