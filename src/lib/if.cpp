DEFORM(if, obj, env, {
  auto test = car(obj);
  auto then = car(cdr(obj));
  auto otherwise = car(cdr(cdr(obj)));
  if (eval(test, env) != nullptr) {
    return eval(then, env);
  }
  return eval(otherwise, env);
});
