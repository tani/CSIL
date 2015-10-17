DEFORM(defun, obj, env, {
  auto name = car(obj);
  auto args = car(cdr(obj));
  auto body = cdr(cdr(obj));
  defun(global_env, name->atom.symbol, [=](ObjPtr vars, Env env_1) -> ObjPtr {
    for (auto a = args, v = vars; v != nullptr && a != nullptr;
         a = cdr(a), v = cdr(v)) {
      if (car(a)->atom.symbol == "&rest") {
        env_1.variables[car(cdr(a))->atom.symbol] = v;
        break;
      }
      env_1.variables[car(a)->atom.symbol] = car(v);
    }
    ObjPtr result;
    for (auto b = body; b != nullptr; b = cdr(b)) {
      result = eval(car(b), env_1);
    }
    return result;
  });
  return name;
});
