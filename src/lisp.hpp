#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <string>

namespace islisp {
namespace core {
struct Object;
struct Environment;
typedef Environment Env;
typedef std::string Symbol;
typedef std::shared_ptr<Object> ObjPtr;
typedef std::function<ObjPtr(ObjPtr)> Function;
typedef std::function<ObjPtr(ObjPtr,Environment&)> Form;

struct Environment {
  std::unordered_map<Symbol, ObjPtr> functions;
  std::unordered_map<Symbol, ObjPtr> variables;
  std::unordered_map<Symbol, ObjPtr> macros;
};

struct Atom {
  Atom();
  ~Atom();
  enum { INTEGER, FLOAT, CHARACTER, SYMBOL, FUNCTION, FORM, BOOLEAN, NIL} type;
  union {
    bool boolean;
    int integer;
    float real;
    char character;
    Function function;
    Form form;
    Symbol symbol;
  };
};

struct Cons {
  Cons();
  ~Cons();
  ObjPtr car;
  ObjPtr cdr;
};

struct Object {
  Object();
  ~Object();
  bool operator==(Object &);
  enum { CONS, ATOM } type;
  union {
    Cons cons;
    Atom atom;
  };
};
}
}
