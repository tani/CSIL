#include "lisp.hpp"

bool Object::operator==(Object obj) {
  if (type == CONS) {
    return obj.type == CONS && obj.cons.car == cons.car &&
           obj.cons.cdr == cons.cdr;
  }
  switch (atom.type) {
  case Atom::INTEGER:
    return obj.type == ATOM && obj.atom.integer == atom.integer;
    break;
  case Atom::FLOAT:
    return obj.type == ATOM && obj.atom.real == atom.real;
    break;
  case Atom::CHARACTER:
    return obj.type == ATOM && obj.atom.character == atom.character;
    break;
  case Atom::SYMBOL:
    return obj.type == ATOM && obj.atom.symbol == atom.symbol;
    break;
  case Atom::FUNCTION:
    return obj.type == ATOM;
  }
  return false;
}
Atom::Atom() {}
Atom::~Atom() {
  if (type == FUNCTION) {
    function.~function();
  }
}
Cons::Cons(){};
Cons::~Cons() {
  car.reset();
  cdr.reset();
};
Object::Object() {}
Object::~Object() {
  switch (type) {
  case ATOM:
    atom.~Atom();
    break;
  case CONS:
    cons.~Cons();
    break;
  }
}
