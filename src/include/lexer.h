#ifndef __ETA_LANG_LEXER_H
#define __ETA_LANG_LEXER_H

#include <cstdint>
#include <string>
#include <variant>
#include "tokens.h"
#include "types.h"

class Lexer {
public:
  Lexer(const std::string &filename, const std::string &data);
  auto currentchar() const -> char;
  auto forwardcursor() -> void;
  auto pinposition() -> void;
  auto trim() -> void;
  auto dropln() -> void;
  auto end() const -> bool;
  auto token() -> Token;
  auto getlastposition() const -> Position;
  auto getposition() const -> Position;
  auto getlasttoken() const -> Token;
  auto getvalue() const -> const std::variant<std::string, uint8_t> &;
  auto getln() const -> std::string;
  auto getfilename() const -> std::string;

private:
  auto _token() -> Token;
  const std::string &data;
  const std::string &filename;
  Token lasttoken;
  Position position;
  Position lastposition;
  Position lasttokenposition;
  std::variant<std::string, uint8_t> value;
};

#endif
