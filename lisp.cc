#include <vector>
#include <regex>
#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
static std::hash<std::string> intern;
typedef size_t symbol;

struct Atom {
  enum { INTEGER, FLOAT, CHARACTER, SYMBOL } type;
  bool operator==(Atom a) {
    switch (type) {
    case INTEGER:
      return integer == a.integer;
    case FLOAT:
      return real == a.real;
    case SYMBOL:
      return symbol == a.symbol;
    case CHARACTER:
      return character == a.character;
    }
    return false;
  }
  union {
    int integer;
    float real;
    char character;
    size_t symbol;
  };
};

struct Object;
typedef std::shared_ptr<Object> ObjPtr;

struct Cons {
  ObjPtr car;
  ObjPtr cdr;
};

struct Object {
  enum { CONS, ATOM } type;
  Cons cons;
  Atom atom;
};

inline ObjPtr car(ObjPtr obj) { return obj->cons.car; }
inline ObjPtr cdr(ObjPtr obj) { return obj->cons.cdr; }

int print(ObjPtr obj) {
  if (obj == nullptr) {
    std::cout << "nil";
  } else if (obj->type == Object::ATOM) {
    switch (obj->atom.type) {
    case Atom::INTEGER:
      std::cout << obj->atom.integer << " ";
      break;
    case Atom::FLOAT:
      std::cout << obj->atom.real << " ";
      break;
    case Atom::CHARACTER:
      std::cout << "#\\" << obj->atom.character << " ";
      break;
    case Atom::SYMBOL:
      std::cout << obj->atom.symbol << " ";
      break;
    }
  } else {
    std::cout << "(";
    print(obj->cons.car);
    std::cout << " . ";
    print(obj->cons.cdr);
    std::cout << ")";
  }
  return 0;
}

#define _FLOAT "\\d+\\.\\d*|\\d*\\.\\d+"
#define _INTEGER "\\d+"
#define _CHARACTER "#\\\\."
#define _STRING "\"[^\"]*\""
#define _SYMBOL "[[:alnum:]+\\-<>/+&=.?_!$%:@\\[\\]^{}~]+"
#define _PARENTHESIS "[()]"
int tokenize(std::string src, std::vector<std::string> &tokens) {
  std::regex regex(_FLOAT "|" _INTEGER "|" _CHARACTER "|" _STRING "|" _SYMBOL
                          "|" _PARENTHESIS);
  std::copy(std::sregex_token_iterator(src.cbegin(), src.cend(), regex),
            std::sregex_token_iterator(), std::back_inserter(tokens));
  return 0;
}

int parse_atom(std::vector<std::string>::iterator token, ObjPtr obj) {
  obj->type = Object::ATOM;
  if (regex_match(*token, std::regex(_FLOAT))) {
    obj->atom.type = Atom::FLOAT;
    obj->atom.real = std::stof(*token);
  } else if (regex_match(*token, std::regex(_INTEGER))) {
    obj->atom.type = Atom::INTEGER;
    obj->atom.integer = std::stoi(*token);
  } else if (regex_match(*token, std::regex(_SYMBOL))) {
    obj->atom.type = Atom::SYMBOL;
    obj->atom.symbol = intern(*token);
  } else if (regex_match(*token, std::regex(_CHARACTER))) {
    obj->atom.type = Atom::CHARACTER;
    obj->atom.character = token->at(2);
  }
  return 0;
}

#undef _FLOAT
#undef _INTEGER
#undef _CHARACTER
#undef _STRING
#undef _SYMBOL
#undef _PARENTHESIS
int parse_1ist(std::vector<std::string>::iterator token, ObjPtr obj) {
  if (*token == ")") {
    return 1;
  }
  obj->type = Object::CONS;
  obj->cons.car = std::make_shared<Object>();
  obj->cons.cdr = std::make_shared<Object>();
  if (*token == "(") {
    parse_1ist(++token, car(obj));
    for (int cnt = 1; *token != ")" || cnt != 1; ++token) {
      cnt += *token == ")" ? -1 : *token == "(" ? 1 : 0;
    }
  } else {
    parse_atom(token, car(obj));
  }
  if (parse_1ist(++token, cdr(obj))) {
    obj->cons.cdr = nullptr;
  }
  return 0;
}

inline int parse(std::vector<std::string>::iterator token, ObjPtr obj) {
  if (*token == "(") {
    return parse_1ist(++token, obj);
  }
  return parse_atom(token, obj);
}

std::unordered_map<symbol, std::function<ObjPtr(ObjPtr)>> ft;
std::unordered_map<symbol, std::function<ObjPtr(ObjPtr)>> mt;
std::unordered_map<symbol, ObjPtr> vt;

ObjPtr eval(ObjPtr obj) {
  if (obj->type == Object::ATOM) {
    if (obj->atom.type == Atom::SYMBOL) {
      return vt[obj->atom.symbol];
    } else {
      return obj;
    }
  } else if (ft.count(car(obj)->atom.symbol)) {
    auto args = cdr(obj);
    while (args != nullptr) {
      args->cons.car = eval(car(args));
      args = args->cons.cdr;
    }
    return ft[car(obj)->atom.symbol](cdr(obj));
  } else if (mt.count(car(obj)->atom.symbol)) {
    return mt[car(obj)->atom.symbol](cdr(obj));
  }
  return nullptr;
}

int init() {
#define DEFMACRO(name, args, body)                                             \
  mt[intern(#name)] = [](ObjPtr args) -> ObjPtr body
#define DEFUN(name, args, body)                                                \
  ft[intern(#name)] = [](ObjPtr args) -> ObjPtr body

  DEFMACRO(defun, obj, {
    auto name = car(obj);
    auto args = car(cdr(obj));
    auto body = car(cdr(cdr(obj)));
    ft[name->atom.symbol] = [=](ObjPtr vars) -> ObjPtr {
      auto a = args;
      auto v = vars;
      while (v != nullptr && a != nullptr) {
        vt[car(a)->atom.symbol] = v->cons.car;
        a = a->cons.cdr;
        v = v->cons.cdr;
      }
      auto b = body;
      ObjPtr result = nullptr;
      while (b != nullptr) {
        result = eval(car(b));
        b = b->cons.cdr;
      }
      return result;
    };
    return name;
  });

  DEFMACRO(defvar, obj, {
    auto name = car(obj);
    auto var = car(cdr(obj));
    vt[name->atom.symbol] = eval(var);
    return name;
  });

  DEFMACRO(quote, obj, { return car(obj); });

  DEFUN(eq, obj, {
    if (car(obj)->atom == car(cdr(obj))->atom) {
      return car(obj);
    } else {
      return nullptr;
    }
  });

  DEFUN(car, obj, { return car(car(obj)); });

  DEFUN(cdr, obj, { return cdr(car(obj)); });

  DEFUN(cons, obj, {
    auto val = car(obj);
    auto list = car(cdr(obj));
    auto cons = std::make_shared<Object>();
    cons->cons.car = val;
    cons->cons.cdr = list;
    return cons;
  });
  DEFUN(atom, obj,
        { return car(obj)->type == Object::ATOM ? car(obj) : nullptr; });
  DEFMACRO(if, obj, {
    auto test = car(obj);
    auto then = car(cdr(obj));
    auto otherwise = car(cdr(cdr(obj)));
    if (eval(test) != nullptr) {
      return eval(then);
    } else {
      return eval(otherwise);
    }
  });
  return 0;
#undef DEFUN
#undef DEFMACRO
}

int main(int argc, char const *argv[]) {
  init();
  std::string line;
  std::vector<std::string> tokens;
  ObjPtr obj;
  getline(std::cin, line);
  tokenize(line, tokens);
  obj = std::make_shared<Object>();
  parse(tokens.begin(), obj);
  print(eval(obj));
  return 0;
}
