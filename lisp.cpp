#include "object.hpp"

namespace cisl {

static Table vt, ft;

#define DEFUN(name, args, body)                                                \
  auto name = new Function([](const ObjPtr &args)body)
#define DEFMACRO(name, args, body)                                             \
  auto name = new Macro([](const ObjPtr &args)body)
#define DEFVAR(name, var) auto name = var
#define NIL std::static_pointer_cast<Object>(nil)

inline std::shared_ptr<Cons> to_cons(const ObjPtr &obj) {
  return std::static_pointer_cast<Cons>(obj);
}

DEFVAR(nil, std::static_pointer_cast<Object>(std::make_shared<Nil>(Nil())));
DEFMACRO(defun, obj, {
  auto f = to_std_string(to_cons(obj)->car->to_string());
  auto c = to_cons(to_cons(obj)->cdr);
  ft[f] = std::make_shared<Function>(Function(c->car, c->cdr, vt, ft));
  return ft[f];
});

DEFMACRO(defvar, obj, {
  Eval eval(vt, ft);
  auto body = to_cons(to_cons(obj)->cdr);
  auto name = to_std_string(to_cons(obj)->car->to_string());
  vt[name] = eval(body->car);
  return vt[name];
});

DEFUN(car, obj, { return to_cons(obj)->car; });
DEFUN(cdr, obj, { return to_cons(obj)->cdr; });
DEFUN(cons, obj, {
  auto c = to_cons(obj);
  auto cdr = to_cons(c->cdr);
  return std::make_shared<Cons>(Cons(c->car, cdr->car));
});
DEFUN(atom, obj, { return obj->type() == CONS ? NIL : obj; });
DEFUN(eq, obj, {
  auto a = to_cons(obj)->car;
  auto b = to_cons(to_cons(obj)->cdr)->car;
  return NIL;
});
}
