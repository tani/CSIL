DEFUN(eq, obj, env, {
  if (car(obj) == car(cdr(obj))) {
    return car(obj);
  } else {
    return nullptr;
  }
});
