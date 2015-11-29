#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace form {
using namespace core;
class Apply {
public:
  ObjPtr operator()(ObjPtr exp, Environment& env) { return cadr(exp)->atom.function(caddr(exp)); }
};
}
}
