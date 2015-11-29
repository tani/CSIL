#include "../util.hpp"
#include "../lisp.hpp"

namespace islisp {
namespace form {
using namespace core;
class Quote {
public:
  ObjPtr operator()(ObjPtr exp, Environment& env) { return car(exp); }
};
}
}
