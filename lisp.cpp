#include "object.hpp"

namespace cisl {

static Table vt, ft;
inline std::shared_ptr<Cons> to_cons(const ObjPtr &obj) {
  return std::static_pointer_cast<Cons>(obj);
}

#define CAR(name) to_cons(name)->car
#define CDR(name) to_cons(name)->cdr
#define CADR(name) CAR(CDR(name))
#define CDDR(name) CDR(CDR(name))
#define CONS(val, list) std::make_shared<Cons>(Cons(val, list))
#define EQ(a, b) a == b
#define IF(test, then, otherwise) (test) ? (then) : (otherwise)
#define TYPE(name) name->type()
#define AND(a, b) a &&b;
#define PRINT_TO_STRING(obj) obj->to_string()
#define PRINC_TO_STRING(obj) to_std_string(PRINT_TO_STRING(obj))
#define SETF(a, b) a = b
#define AREF(obj, index) obj[index]
#define LAMBDA(args, body)                                                     \
  std::make_shared<Function>(Function(args, body, vt, ft))
#define FUNCALL(obj, args) (*obj)(args)
#define DEFUN(name, args, body)                                                \
  auto name = new Function([](const ObjPtr &args)body)
#define DEFMACRO(name, args, body)                                             \
  auto name = new Macro([](const ObjPtr &args)body)
#define DEFVAR(name, var) auto name = var

DEFVAR(nil, std::static_pointer_cast<Object>(std::make_shared<Nil>(Nil())));
DEFMACRO(defun, obj, {
  DEFVAR(f, PRINC_TO_STRING(CAR(obj)));
  SETF(AREF(ft, f), LAMBDA(CADR(obj), CDDR(obj)));
  return AREF(ft, f);
});
DEFMACRO(defvar, obj, {
  DEFVAR(eval, new Eval(vt, ft));
  DEFVAR(v, PRINC_TO_STRING(CAR(obj)));
  SETF(AREF(vt, v), FUNCALL(eval, CADR(obj)));
  return AREF(vt, v);
});
DEFUN(car, obj, { return CAR(obj); });
DEFUN(cdr, obj, { return CDR(obj); });
DEFUN(cons, obj, { return CONS(CAR(obj), CADR(obj)); });
DEFUN(atom, obj, { return IF(EQ(TYPE(obj), CONS), nil, obj); });
DEFUN(eq, obj, { return nil; });
}
