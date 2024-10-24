#ifndef __ETA_LANG_TOKENS_H
#define __ETA_LANG_TOKENS_H

#include <cstdint>

enum Token : uint8_t {
  // KEYWORDS
  TIMPORT,
  TSTRUCT,
  TMUT,
  TFOR,
  TIF,
  TELSE,
  TRETURN,
  TBREAK,
  TCONTINUE,
  TSWITCH,
  TCASE,
  TEXTERN,
  TENUM,
  TDEFER,
  TFUNC,

  TDIGIT,

  // SPECIAL CHAR
  TOPAREN,
  TCPAREN,
  TOCURLY,
  TCCURLY,
  TOSQR,
  TCSQR,
  TCOMMA,
  TSEMICOLON,
  TCOLON,
  TGRT,
  TLES,
  TDOT,
  TADD,
  TSUB,
  TDIV,
  TMUL,
  TEXP,
  TAND,
  TPER,
  TEQL,

  // EXTRAS
  TIDENTIFIER,
  TUNKNOWN,
  NONE,
  TEOF,
  __TCOUNT__,
};

const char *const TokenNames[__TCOUNT__] = {
  "import",
  "struct",
  "mut",
  "for",
  "if",
  "else",
  "return",
  "break",
  "continue",
  "switch",
  "case",
  "extern",
  "enum",
  "defer",
  "function",

  "digit",

  "open parentheses '('",
  "close parentheses ')'",
  "open curly brace '{'",
  "close curly brace '}'",
  "open square bracket '['",
  "close square bracket ']'",
  "comma ','",
  "semi-colon ';'",
  "colon ':'",
  "greater than '>'",
  "less than '<'",
  "dot '.'",
  "add '+'",
  "sub '-'",
  "div '/'",
  "mul '*'",
  "exponent '^'",
  "and '&'",
  "percent '%'",
  "equal '='",
  "identifier",
  "unknown token",
  "none",
  "end of file",
};

#endif
