DEFUN(car, obj, env, { return car(car(obj)); });

DEFUN(cdr, obj, env, { return cdr(car(obj)); });

DEFUN(cons, obj, env, {
  auto val = car(obj);
  auto list = car(cdr(obj));
  auto cons = std::make_shared<Object>();
  createCons(cons);
  cons->cons.car = val;
  cons->cons.cdr = list;
  return cons;
});
