#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace macro {
using namespace core;
class Defun {
public:
  ObjPtr operator()(ObjPtr exp) {
    auto name = car(exp);
    auto args = cadr(exp);
    auto body = cddr(exp);
    auto define = std::make_shared<Object>();
    auto lambda = std::make_shared<Object>();
    createAtom(define, "define");
    createAtom(lambda, "lambda");
    return cons(define, cons(name, cons(cons(lambda, cons(args, cons(body, nullptr))), nullptr)));
  }
};
}
}
