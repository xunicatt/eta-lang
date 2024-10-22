#ifndef __GRIT_LANG_LEXER_H
#define __GRIT_LANG_LEXER_H

#include "tokens.h"
#include "types.h"
#include <cstdint>
#include <string>
#include <variant>

class Lexer {
public:
  Lexer(const std::string &data);
  auto currentchar() const -> char;
  auto forwardcursor() -> void;
  auto pinposition() -> void;
  auto trim() -> void;
  auto dropln() -> void;
  auto end() const -> bool;
  auto token() -> Token;
  auto getlastposition() const -> Position;
  auto getlasttoken() const -> Token;

private:
  auto _token() -> Token;
  const std::string &data;
  Token lasttoken;
  Position position;
  Position lastposition;
  std::variant<std::string, uint8_t> value;
};

#endif
