#include <functional>
#include <memory>

typedef size_t symbol;
struct Object;
typedef std::shared_ptr<Object> ObjPtr;

struct Atom {
  enum { INTEGER, FLOAT, CHARACTER, SYMBOL, FUNCTION } type;
  union {
    int integer;
    float real;
    char character;
    size_t symbol;
  };
  std::function<ObjPtr(ObjPtr)> function;
};

struct Cons {
  ObjPtr car;
  ObjPtr cdr;
};

struct Object {
  bool operator==(Object);
  enum { CONS, ATOM } type;
  Cons cons;
  Atom atom;
};

ObjPtr car(ObjPtr);
ObjPtr cdr(ObjPtr);
