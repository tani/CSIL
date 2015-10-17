#include <functional>
#include <memory>

typedef size_t symbol;
struct Object;
typedef std::shared_ptr<Object> ObjPtr;

struct Atom {
  Atom();
  ~Atom();
  enum { INTEGER, FLOAT, CHARACTER, SYMBOL, FUNCTION } type;
  union {
    int integer;
    float real;
    char character;
    size_t symbol;
    std::function<ObjPtr(ObjPtr)> function;
  };
};

struct Cons {
  Cons();
  ~Cons();
  ObjPtr car;
  ObjPtr cdr;
};

struct Object {
  Object();
  ~Object();
  bool operator==(Object);
  enum { CONS, ATOM } type;
  union {
    Cons cons;
    Atom atom;
  };
};

inline ObjPtr car(ObjPtr obj) { return obj->cons.car; }
inline ObjPtr cdr(ObjPtr obj) { return obj->cons.cdr; }
inline void createCons(ObjPtr obj) {
  obj->type = Object::CONS;
  new (&obj->cons) Cons();
}
inline void createAtom(ObjPtr obj) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
}
inline void createFunction(ObjPtr obj, std::function<ObjPtr(ObjPtr)> func) {
  obj->type = Object::ATOM;
  new (&obj->atom) Atom();
  obj->atom.type = Atom::FUNCTION;
  new (&obj->atom.function) std::function<ObjPtr(ObjPtr)>(func);
}
