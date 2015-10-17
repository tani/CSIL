DEFUN(apply, obj, env, { return car(obj)->atom.function(car(cdr(obj)), env); });
