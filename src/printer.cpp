#include "lisp.hpp"
#include <ostream>

namespace islisp {
namespace io {
using namespace core;
int print(std::ostream &output, ObjPtr obj) {
  if (obj == nullptr) {
    output << "nil";
  } else if (obj->type == Object::ATOM) {
    switch (obj->atom.type) {
    case Atom::BOOLEAN:
      output << "t";
      break;
    case Atom::INTEGER:
      output << obj->atom.integer;
      break;
    case Atom::FLOAT:
      output << obj->atom.real;
      break;
    case Atom::CHARACTER:
      output << "#\\" << obj->atom.character;
      break;
    case Atom::SYMBOL:
      output << obj->atom.symbol;
      break;
    case Atom::FUNCTION:
      output << "#<FUNCTION>";
      break;
    case Atom::FORM:
      output << "#<FORM>";
      break;
    }
  } else {
    output << "(";
    print(output, obj->cons.car);
    output << " . ";
    print(output, obj->cons.cdr);
    output << ")";
  }
  return 0;
}
}
}
