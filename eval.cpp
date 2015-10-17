#include "lisp.hpp"
#include <unordered_map>
#include <iostream>
#define DEF(tb, name, args, body)                                              \
  tb[intern(#name)] = std::make_shared<Object>();                              \
  tb[intern(#name)]->type = Object::ATOM;                                      \
  new (&tb[intern(#name)]->atom) Atom();                                       \
  tb[intern(#name)]->atom.type = Atom::FUNCTION;                               \
  new (&tb[intern(#name)]->atom.function)                                      \
      std::function<ObjPtr(ObjPtr)>([=](ObjPtr args) -> ObjPtr body)
#define DEFMACRO(name, args, body) DEF(mt, name, args, body)
#define DEFUN(name, args, body) DEF(ft, name, args, body)
#define DEFORM(name, args, body) DEF(sf, name, args, body)

static std::hash<std::string> intern;

static std::unordered_map<symbol, ObjPtr> ft;
static std::unordered_map<symbol, ObjPtr> mt;
static std::unordered_map<symbol, ObjPtr> sf;
static std::unordered_map<symbol, ObjPtr> vt;
ObjPtr eval(ObjPtr obj) {
  if (obj->type == Object::ATOM) {
    if (obj->atom.type == Atom::SYMBOL) {
      return vt[obj->atom.symbol];
    } else {
      return obj;
    }
  } else if (ft.count(car(obj)->atom.symbol) != 0) {
    auto args = cdr(obj);
    while (args != nullptr) {
      args->cons.car = eval(car(args));
      args = args->cons.cdr;
    }
    return ft[car(obj)->atom.symbol]->atom.function(cdr(obj));
  } else if (mt.count(car(obj)->atom.symbol) != 0) {
    return eval(mt[car(obj)->atom.symbol]->atom.function(cdr(obj)));
  } else if (sf.count(car(obj)->atom.symbol) != 0) {
    return sf[car(obj)->atom.symbol]->atom.function(cdr(obj));
  }

  return nullptr;
}

int init() {

  DEFMACRO(defun, obj, {
    auto name = car(obj);
    auto args = car(cdr(obj));
    auto body = cdr(cdr(obj));
    ft[name->atom.symbol] = std::make_shared<Object>();
    ft[name->atom.symbol]->type = Object::ATOM;
    new (&ft[name->atom.symbol]->atom) Atom();
    ft[name->atom.symbol]->atom.type = Atom::FUNCTION;
    ft[name->atom.symbol]->atom.function = [=](ObjPtr vars) -> ObjPtr {
      auto a = args;
      auto v = vars;
      while (v != nullptr && a != nullptr) {
        vt[car(a)->atom.symbol] = v->cons.car;
        a = a->cons.cdr;
        v = v->cons.cdr;
      }
      auto b = body;
      ObjPtr result = nullptr;
      while (b != nullptr) {
        result = eval(car(b));
        b = b->cons.cdr;
      }
      return result;
    };
    return name;
  });

  DEFMACRO(defvar, obj, {
    auto name = car(obj);
    auto var = car(cdr(obj));
    vt[name->atom.symbol] = eval(var);
    return name;
  });

  DEFORM(quote, obj, { return car(obj); });

  DEFUN(eq, obj, {
    if (car(obj) == car(cdr(obj))) {
      return car(obj);
    } else {
      return nullptr;
    }
  });

  DEFUN(car, obj, { return car(car(obj)); });

  DEFUN(cdr, obj, { return cdr(car(obj)); });

  DEFUN(cons, obj, {
    auto val = car(obj);
    auto list = car(cdr(obj));
    auto cons = std::make_shared<Object>();
    new (&cons->cons) Cons();
    cons->cons.car = val;
    cons->cons.cdr = list;
    return cons;
  });

  DEFUN(atom, obj,
        { return car(obj)->type == Object::ATOM ? car(obj) : nullptr; });
  DEFORM(if, obj, {
    auto test = car(obj);
    auto then = car(cdr(obj));
    auto otherwise = car(cdr(cdr(obj)));
    if (eval(test) != nullptr) {
      return eval(then);
    }
    return eval(otherwise);
  });

  DEFORM(lambda, obj, {
    auto args = car(obj);
    auto body = cdr(obj);
    auto lambda = std::make_shared<Object>();
    lambda->type = Object::ATOM;
    new (&lambda->atom) Atom();
    lambda->atom.type = Atom::FUNCTION;
    lambda->atom.function = [=](ObjPtr vars) {
      auto a = args;
      auto v = vars;
      while (v != nullptr && a != nullptr) {
        vt[car(a)->atom.symbol] = v->cons.car;
        a = a->cons.cdr;
        v = v->cons.cdr;
      }
      auto b = body;
      ObjPtr result = nullptr;
      while (b != nullptr) {
        result = eval(car(b));
        b = b->cons.cdr;
      }
      return result;
    };
    return lambda;
  });

  DEFUN(apply, obj, { return car(obj)->atom.function(car(cdr(obj))); });

  DEFORM(function, obj, { return ft[car(obj)->atom.symbol]; });
  return 0;
}
#undef DEFUN
#undef DEFMACRO
#undef DEFORM
#undef DEF
