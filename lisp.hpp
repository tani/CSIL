/*
Copyright 2015 TANIGUCHI Masaya. All rights reserved.
*/
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

namespace cisl {

typedef enum {
  CONS,
  INTEGER,
  FLOAT,
  CHARACTER,
  SYMBOL,
  FUNCTION,
  MACRO,
  ARRAY,
  STRING
} Type;

class String;

class Object {
public:
  virtual Type type() const = 0;
  virtual String to_string() const = 0;
};
typedef std::shared_ptr<Object> ObjPtr;
typedef std::function<ObjPtr(const ObjPtr &)> FuncObj;
typedef std::function<ObjPtr(const ObjPtr &, const ObjPtr &)> FuncObj2;

class Number : public Object {};

class Integer : public Number {
public:
  Integer(int value);
  Type type() const override;
  String to_string() const override;

private:
  int value;
};

class Float : public Number {
public:
  Float(float value);
  Type type() const override;
  String to_string() const override;

private:
  float value;
};

class Character : public Object {
public:
  Character(char value);
  Type type() const override;
  String to_string() const override;
  friend char raw(std::shared_ptr<Character>);

private:
  char value;
};

class Array : public Object {
public:
  Array();
  Array(std::vector<ObjPtr> value);
  Type type() const override;
  String to_string() const override;
  std::vector<ObjPtr> value;
};

class String : public Array {
public:
  String();
  String(std::vector<std::shared_ptr<Character>> value);
  Type type() const override;
  String to_string() const override;
};

class List : public Object {};

class Cons : public List {
public:
  Cons(const ObjPtr &hd, const ObjPtr &tl);
  Type type() const override;
  String to_string() const override;
  ObjPtr car() const;
  ObjPtr cdr() const;
  ObjPtr set_car(const ObjPtr &obj);
  ObjPtr set_cdr(const ObjPtr &obj);

private:
  ObjPtr hd;
  ObjPtr tl;
};

class Symbol : public Object {
public:
  Symbol(String value);
  Type type() const override;
  String to_string() const override;

private:
  String value;
};

ObjPtr last(const ObjPtr &obj);

typedef std::unordered_map<std::string, ObjPtr> Table;

class Macro : public Object {
  // Macro := Cell* -> Cell*
public:
  Macro(const ObjPtr &args, const ObjPtr &body, Table &vt, Table &ft);
  Type type() const override;
  String to_string() const override;
  ObjPtr call(const ObjPtr &args) const;

private:
  std::function<ObjPtr(const ObjPtr &)> macro;
};

class Function : public Object {
  // Function := Cell* -> Object*
public:
  Function(const ObjPtr &args, const ObjPtr &body, Table &vt, Table &ft);
  Type type() const override;
  String to_string() const override;
  ObjPtr call(const ObjPtr &args) const;

private:
  std::function<ObjPtr(const ObjPtr &)> function;
};

class Eval {
public:
  Eval(Table &vt, Table &ft);
  ObjPtr operator()(const ObjPtr &exp);

private:
  Table vt;
  Table ft;
};
}
