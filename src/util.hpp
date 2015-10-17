#pragma once
#include "lisp.hpp"

inline ObjPtr car(ObjPtr obj) { return obj->cons.car; }
inline ObjPtr cdr(ObjPtr obj) { return obj->cons.cdr; }

inline void createCons(ObjPtr obj) {
  obj->type = Object::CONS;
  new (&obj->cons) Cons();
}
inline void createAtom(ObjPtr obj) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
}
inline void createAtom(ObjPtr obj, int value) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
  obj->atom.type = Atom::INTEGER;
  obj->atom.integer = value;
}
inline void createAtom(ObjPtr obj, float value) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
  obj->atom.type = Atom::FLOAT;
  obj->atom.real = value;
}
inline void createAtom(ObjPtr obj, char value) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
  obj->atom.type = Atom::CHARACTER;
  obj->atom.character = value;
}
inline void createAtom(ObjPtr obj, Symbol value) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
  obj->atom.type = Atom::SYMBOL;
  new (&obj->atom.symbol) std::string(value);
}
inline void createAtom(ObjPtr obj, Function value) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
  obj->atom.type = Atom::FUNCTION;
  new (&obj->atom.function) Function(value);
}
