#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace function {
using namespace core;
class Eq {
public:
  ObjPtr operator()(ObjPtr exp) {
    if (*(car(exp)) == *(cadr(exp))) {
      return createAtom(std::make_shared<Object>(), true);
    } else {
      return nullptr;
    }
  }
};
}
}
