#include <regex>
#include <vector>
#include <string>
#include "lisp.hpp"

static std::hash<std::string> intern;

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

int parse(std::vector<std::string>::iterator token, ObjPtr obj) {
  if (*token == "(") {
    return parse_1ist(++token, obj);
  }
  return parse_atom(token, obj);
}
