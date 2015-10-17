#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <string>
typedef std::string Symbol;
struct Object;
struct Env;
typedef std::shared_ptr<Object> ObjPtr;
typedef std::function<ObjPtr(ObjPtr, Env)> Function;

struct Env {
  std::unordered_map<Symbol, ObjPtr> functions;
  std::unordered_map<Symbol, ObjPtr> variables;
  std::unordered_map<Symbol, ObjPtr> macros;
  std::unordered_map<Symbol, ObjPtr> forms;
};

struct Atom {
  Atom();
  ~Atom();
  enum { INTEGER, FLOAT, CHARACTER, SYMBOL, FUNCTION } type;
  union {
    int integer;
    float real;
    char character;
    Function function;
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
  bool operator==(Object);
  enum { CONS, ATOM } type;
  union {
    Cons cons;
    Atom atom;
  };
};
