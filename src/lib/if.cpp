#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace core {
ObjPtr eval(ObjPtr,Environment&);
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
}
}
