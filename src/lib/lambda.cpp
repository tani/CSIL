DEFORM(lambda, obj, env, {
  auto args = car(obj);
  auto body = cdr(obj);
  auto lambda = std::make_shared<Object>();
  createAtom(lambda, [=](ObjPtr vars, Env env_1) -> ObjPtr {
    for (auto a = args, v = vars; v != nullptr && a != nullptr;
         a = cdr(a), v = cdr(v)) {
      env_1.variables[car(a)->atom.symbol] = car(v);
    }
    ObjPtr result = nullptr;
    for (auto b = body; b != nullptr; b = cdr(b)) {
      result = eval(car(b), env_1);
    }
    return result;
  });
  return lambda;
});
