#include "lisp.hpp"
#include <ostream>
int print(std::ostream& output,ObjPtr obj) {
  if (obj == nullptr) {
    output << "nil";
  } else if (obj->type == Object::ATOM) {
  switch (obj->atom.type) {
    case Atom::INTEGER:   output << obj->atom.integer;            break;
    case Atom::FLOAT:     output << obj->atom.real;               break;
    case Atom::CHARACTER: output << "#\\" << obj->atom.character; break;
    case Atom::SYMBOL:    output << obj->atom.symbol;             break;
    case Atom::FUNCTION:  output << "#<FUNCTION>";                break;
    }
  } else {
    output << "(";
    print(output,obj->cons.car);
    output << " . ";
    print(output,obj->cons.cdr);
    output << ")";
  }
  return 0;
}