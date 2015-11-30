#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace function {
using namespace core;
class Atom {
public:
  ObjPtr operator()(ObjPtr exp) {
    if (car(exp)->type == Object::ATOM) {
      return createAtom(std::make_shared<Object>(), true);
    } else {
      return nil();
    }
  }
};
}
}
