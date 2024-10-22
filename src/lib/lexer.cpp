#include "lexer.h"
#include <sys/types.h>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <string_view>
#include "tokens.h"
#include "types.h"

static const std::map<std::string_view, Token> Keywords = {
  {"import",   TIMPORT  },
  {"struct",   TSTRUCT  },
  {"pub",      TPUB     },
  {"mut",      TMUT     },
  {"for",      TFOR     },
  {"if",       TIF      },
  {"else",     TELSE    },
  {"return",   TRETURN  },
  {"break",    TBREAK   },
  {"continue", TCONTINUE},
  {"switch",   TSWITCH  },
  {"case",     TCASE    },
  {"extern",   TEXTERN  },
  {"enum",     TENUM    },
};

static const std::map<char, Token> SpecialChars = {
  {'(', TOPAREN   },
  {')', TCPAREN   },
  {'{', TOCURLY   },
  {'}', TCCURLY   },
  {'[', TOSQR     },
  {']', TCSQR     },
  {',', TCOMMA    },
  {';', TSEMICOLON},
  {':', TCOLON    },
  {'>', TGRT      },
  {'<', TLES      },
  {'.', TDOT      },
  {'+', TADD      },
  {'-', TSUB      },
  {'/', TDIV      },
  {'*', TMUL      },
  {'^', TEXP      },
  {'&', TAND      },
  {'%', TPER      },
  {'=', TEQL      },
};

Lexer::Lexer(const std::string &data) : data(data) {
}

auto Lexer::currentchar() const -> char {
  if (end()) {
    return 0;
  }
  return data[position.cursor];
}

auto Lexer::forwardcursor() -> void {
  if (!end()) {
    position.cursor++;
    if (!end() && currentchar() == '\n') {
      position.row++;
      position.linebeg = position.cursor + 1;
    }
  }
}

auto Lexer::pinposition() -> void {
  lastposition = position;
}

auto Lexer::trim() -> void {
  while (!end() && std::isspace(currentchar())) {
    forwardcursor();
  }
}

auto Lexer::dropln() -> void {
  while (!end() && currentchar() != '\n') {
    forwardcursor();
  }
}

auto Lexer::end() const -> bool {
  return position.cursor >= data.length();
}
auto Lexer::getlastposition() const -> Position {
  return lastposition;
}
auto Lexer::getlasttoken() const -> Token {
  return lasttoken;
}

auto Lexer::_token() -> Token {
  trim();
  pinposition();

  if (end()) {
    return TEOF;
  }

  if (std::isalpha(currentchar()) || currentchar() == '_') {
    size_t beg = position.cursor;

    while (!end() && (std::isalnum(currentchar()) || currentchar() == '_')) {
      forwardcursor();
    }

    std::string identifier = data.substr(beg, position.cursor - beg);
    if (Keywords.find(identifier.c_str()) != Keywords.end()) {
      return Keywords.at(identifier.c_str());
    }

    value = identifier;
    return TIDENTIFIER;
  }

  if (std::isdigit(currentchar())) {
    value = static_cast<uint8_t>(currentchar() - '0');
    forwardcursor();
    return TDIGIT;
  }

  if (SpecialChars.find(currentchar()) != SpecialChars.end()) {
    char c = currentchar();
    forwardcursor();
    return SpecialChars.at(c);
  }

  return TUNKNOWN;
}

auto Lexer::token() -> Token {
  return lasttoken = _token();
}
