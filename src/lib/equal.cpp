#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace function {
using namespace core;
class Eq {
public:
  ObjPtr operator()(ObjPtr exp) {
    return *(car(exp)) == *(cadr(exp)) ? car(exp) : nullptr;
  }
};
}
}
