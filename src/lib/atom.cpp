#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace function {
using namespace core;
class Atom {
public:
  ObjPtr operator()(ObjPtr exp) {
    return car(exp)->type == Object::ATOM ? car(exp) : nullptr;
  }
};
}
}
