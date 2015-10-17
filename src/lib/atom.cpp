DEFUN(atom, obj, env,
      { return car(obj)->type == Object::ATOM ? car(obj) : nullptr; });
