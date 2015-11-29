#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace core {
ObjPtr eval(ObjPtr,Environment&);
}
namespace form {
using namespace core;
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
}
}
