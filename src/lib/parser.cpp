#include <parser.h>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>
#include "ast.h"
#include "logerr.h"
#include "tokens.h"

auto ParseNumber(Lexer& l) -> ExpressionRef {
  std::string res;

  while (!l.end() && (l.getlasttoken() == TDIGIT || l.getlasttoken() == TDOT)) {
    res += l.currentchar();
    l.token();
  }

  if (res.find('.') == std::string::npos) {
    uint64_t value = std::stoull(res);
    return std::make_unique<Number>(value, SIGNED, S64);
  }

  double value = std::stold(res);
  return std::make_unique<Number>(value, DOUBLE, S64);
}

auto ParseParen(Lexer& l) -> ExpressionRef {
  l.token();
  ExpressionRef expr = ParseExpression(l);

  if (expr == nullptr) {
    return nullptr;
  }

  if (l.getlasttoken() != TCPAREN) {
    return logerr("expect ')' in:\n" + l.getln());
  }

  l.token();
  return expr;
}

auto ParseIdentifier(Lexer& l) -> ExpressionRef {
  std::string name = std::get<std::string>(l.getvalue());
}
