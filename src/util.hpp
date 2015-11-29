#pragma once
#include "lisp.hpp"

inline void createCons(ObjPtr obj) {
  new (&obj->cons) Cons();
  obj->type = Object::CONS;
}
inline void createAtom(ObjPtr obj) {
  new (&obj->atom) Atom();
  obj->type = Object::ATOM;
}
inline void createAtom(ObjPtr obj, int value) {
  new (&obj->atom) Atom();
  obj->type = Object::ATOM;
  obj->atom.type = Atom::INTEGER;
  obj->atom.integer = value;
}
inline void createAtom(ObjPtr obj, float value) {
  new (&obj->atom) Atom();
  obj->type = Object::ATOM;
  obj->atom.type = Atom::FLOAT;
  obj->atom.real = value;
}
inline void createAtom(ObjPtr obj, char value) {
  new (&obj->atom) Atom();
  obj->type = Object::ATOM;
  obj->atom.type = Atom::CHARACTER;
  obj->atom.character = value;
}
inline void createAtom(ObjPtr obj, Symbol value) {
  new (&obj->atom) Atom();
  new (&obj->atom.symbol) std::string(value);
  obj->type = Object::ATOM;
  obj->atom.type = Atom::SYMBOL;
}
inline void createAtom(ObjPtr obj, Function value) {
  new (&obj->atom) Atom();
  new (&obj->atom.function) Function(value);
  obj->type = Object::ATOM;
  obj->atom.type = Atom::FUNCTION;
}

inline ObjPtr car(ObjPtr obj) { return obj->cons.car; }
inline ObjPtr cdr(ObjPtr obj) { return obj->cons.cdr; }
inline ObjPtr cddr(ObjPtr obj) { return cdr(cdr(obj)); }
inline ObjPtr cadr(ObjPtr obj) { return car(cdr(obj)); }
inline ObjPtr caddr(ObjPtr obj) { return car(cdr(cdr(obj)));}
inline ObjPtr cadddr(ObjPtr obj) { return car(cdr(cdr(cdr(obj))));}
inline ObjPtr cons(ObjPtr val,ObjPtr list) {
  auto cons = std::make_shared<Object>();
  createCons(cons);
  cons->cons.car = val;
  cons->cons.cdr = list;
  return cons;
}
