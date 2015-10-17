DEFMACRO(defvar, obj, env, {
  auto name = car(obj);
  auto var = car(cdr(obj));
  global_env.variables.at(name->atom.symbol) = eval(var, env);
  return name;
});
