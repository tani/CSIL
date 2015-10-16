#include "lisp.hpp"
#include <iostream>
int print(ObjPtr obj) {
  if (obj == nullptr) {
    std::cout << "nil";
  } else if (obj->type == Object::ATOM) {
    switch (obj->atom.type) {
    case Atom::INTEGER:
      std::cout << obj->atom.integer << " ";
      break;
    case Atom::FLOAT:
      std::cout << obj->atom.real << " ";
      break;
    case Atom::CHARACTER:
      std::cout << "#\\" << obj->atom.character << " ";
      break;
    case Atom::SYMBOL:
      std::cout << obj->atom.symbol << " ";
      break;
    case Atom::FUNCTION:
      std::cout << "#<FUNCTION> ";
      break;
    }
  } else {
    std::cout << "(";
    print(obj->cons.car);
    std::cout << " . ";
    print(obj->cons.cdr);
    std::cout << ")";
  }
  return 0;
}
