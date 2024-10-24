#include <parser.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "ast.h"
#include "logerr.h"
#include "tokens.h"

static const std::map<const std::string, VariableType> VariableTypeMap = {
  {"i8",     VTI8    },
  {"i16",    VTI16   },
  {"i32",    VTI32   },
  {"i64",    VTI64   },
  {"u8",     VTU8    },
  {"u16",    VTU16   },
  {"u32",    VTU32   },
  {"u64",    VTU64   },
  {"f32",    VTF32   },
  {"f64",    VTF64   },
  {"bool",   VTBOOL  },
  {"string", VTSTRING},
  {"struct", VTSTRUCT},
};

static const std::map<Token, int8_t> BinaryOpPrec = {
  {TGRT, 10},
  {TADD, 20},
  {TSUB, 20},
  {TMUL, 40},
};

static auto GetTokenPrec(Token t) -> int8_t {
  if (BinaryOpPrec.find(t) == BinaryOpPrec.end()) {
    return -1;
  }

  return BinaryOpPrec.at(t);
}

auto ParseNumber(Lexer& l) -> ExpressionRef {
  std::string res;
  bool neg = l.currentchar() == '-';
  if (neg) l.token();

  while (!l.end() && (l.getlasttoken() == TDIGIT || l.getlasttoken() == TDOT)) {
    res += l.currentchar();
    l.token();
  }

  if (res.find('.') == std::string::npos) {
    uint64_t value = std::stoull(res);
    return std::make_unique<Number>(value, neg ? NTNEGINT : NTPOSINT);
  }

  double value = std::stold(res);
  return std::make_unique<Number>(value, neg ? NTNEGFLT : NTPOSFLT);
}

auto ParseParen(Lexer& l) -> ExpressionRef {
  l.token();
  ExpressionRef expr = ParseExpression(l);

  if (expr == nullptr) {
    return nullptr;
  }

  if (l.getlasttoken() != TCPAREN) {
    return logerr(l, "expected ')'");
  }

  l.token();
  return expr;
}

auto ParseIdentifier(Lexer& l) -> ExpressionRef {
  std::string name = std::get<std::string>(l.getvalue());

  if (l.token() == TCOLON) {
    VariableKind kind = VKCONST;

    if (l.token() == TMUT) {
      kind = VKMUT;
      l.token();
    }

    if (l.getlasttoken() != TIDENTIFIER) {
      return logerr(l, "expected a type");
    }

    VariableType type = VariableTypeMap.at(std::get<std::string>(l.getvalue()));
    return std::make_unique<Variable>(name, type, kind);
  }

  if (l.getlasttoken() != TOPAREN) {
    return logerr(l, "unknown identifier");
  }

  std::vector<ExpressionRef> args{};

  if (l.token() != TCPAREN) {
    while (true) {
      if (auto arg = ParseExpression(l)) {
        args.push_back(std::move(arg));
      } else {
        return nullptr;
      }

      if (l.token() == TCPAREN) {
        break;
      }

      if (l.getlasttoken() != TCOMMA) {
        return logerr(l, "expected ')' or ',' in argument list");
      }

      l.token();
    }
  }

  l.token();
  return std::make_unique<FunctionCall>(name, std::move(args));
}

auto ParseExpression(Lexer& l) -> ExpressionRef {
  ExpressionRef lhs = ParsePrimary(l);
  if (lhs == nullptr) {
    return nullptr;
  }

  return ParseBinary(l, 0, std::move(lhs));
}

auto ParsePrimary(Lexer& l) -> ExpressionRef {
  switch (l.getlasttoken()) {
    default: return logerr(l, "unknown token");
    case TEOF: return logerr(l, "unexpected end of file");
    case TIDENTIFIER: return ParseIdentifier(l);
    case TDIGIT:
    case TSUB: return ParseNumber(l);
    case TOPAREN: return ParseParen(l);
  }
}

auto ParseBinary(Lexer& l, int opprec, ExpressionRef lhs) -> ExpressionRef {
  while (true) {
    int8_t tokenprec = GetTokenPrec(l.getlasttoken());
    if (tokenprec < opprec) {
      return lhs;
    }

    Token op = l.getlasttoken();
    l.token();
    ExpressionRef rhs = ParsePrimary(l);
    if (rhs == nullptr) {
      return nullptr;
    }

    int8_t nextprec = GetTokenPrec(l.getlasttoken());
    if (tokenprec < nextprec) {
      rhs = ParseBinary(l, tokenprec + 1, std::move(rhs));
      if (rhs == nullptr) {
        return nullptr;
      }
    }

    lhs =
      std::make_unique<BinaryExpression>(op, std::move(lhs), std::move(rhs));
  }
}
