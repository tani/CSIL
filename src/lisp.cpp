#include "lisp.hpp"

namespace islisp {
namespace core {
bool Object::operator==(Object &obj) {
  if (type == CONS) {
    return obj.type == CONS
        && *(obj.cons.car) == *(cons.car)
        && *(obj.cons.cdr) == *(cons.cdr);
  }
  switch (atom.type) {
  case Atom::NIL:
    return obj.type == ATOM && obj.atom.boolean == atom.boolean;
  case Atom::BOOLEAN:
    return obj.type == ATOM && obj.atom.boolean == atom.boolean;
  case Atom::INTEGER:
    return obj.type == ATOM && obj.atom.integer == atom.integer;
  case Atom::FLOAT:
    return obj.type == ATOM && obj.atom.real == atom.real;
  case Atom::CHARACTER:
    return obj.type == ATOM && obj.atom.character == atom.character;
  case Atom::SYMBOL:
    return obj.type == ATOM && obj.atom.symbol == atom.symbol;
  case Atom::FUNCTION:
    return obj.type == ATOM;
  case Atom::FORM:
    return obj.type == ATOM;
  }
  return false;
}
Atom::Atom() {}
Atom::~Atom() {
  switch (type) {
  case FUNCTION:
    function.~function();
    break;
  case FORM:
    form.~function();
    break;
  case SYMBOL:
    symbol.~basic_string();
    break;
  default:
    break;
  }
}
Cons::Cons(){};
Cons::~Cons(){};
Object::Object() {}
Object::~Object() {
  switch (type) {
  case ATOM:
    atom.~Atom();
    break;
  case CONS:
    cons.~Cons();
    break;
  default:
    break;
  }
}
}
}
