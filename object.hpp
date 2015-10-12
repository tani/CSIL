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
  STRING,
  NIL
} Type;

struct String;

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

struct Array : public Object {
  Array();
  Array(std::vector<ObjPtr> value);
  Type type() const override;
  String to_string() const override;
  std::vector<ObjPtr> value;
};

struct String : public Array {
  String();
  String(std::vector<std::shared_ptr<Character>> value);
  Type type() const override;
  String to_string() const override;
};

struct List : public Object {};

struct Cons : public List {
  Cons(const ObjPtr &hd, const ObjPtr &tl);
  Type type() const override;
  String to_string() const override;
  ObjPtr car;
  ObjPtr cdr;
};

class Nil : public List {
public:
  Type type() const override;
  String to_string() const override;
};

class Symbol : public Object {
public:
  Symbol(String value);
  Type type() const override;
  String to_string() const override;

private:
  String value;
};

typedef std::unordered_map<std::string, ObjPtr> Table;

class Macro : public Object {
  // Macro := Cons* -> Cons*
public:
  Macro(std::function<ObjPtr(const ObjPtr &)> macro);
  Macro(const ObjPtr &args, const ObjPtr &body, Table &vt, Table &ft);
  Type type() const override;
  String to_string() const override;
  ObjPtr call(const ObjPtr &args) const;

private:
  std::function<ObjPtr(const ObjPtr &)> macro;
};

class Function : public Object {
  // Function := Cons* -> Object*
public:
  Function(std::function<ObjPtr(const ObjPtr &)> function);
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

std::vector<std::shared_ptr<Character>> to_cisl_string(std::string chars);
std::string to_std_string(String chars);
}
