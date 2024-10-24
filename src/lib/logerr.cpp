#include <logerr.h>
#include <cmath>
#include <cstdio>
#include <string>
#include "lexer.h"
#include "types.h"

auto logerr(const Lexer& l, const std::string& error) -> ExpressionRef {
  Position pos     = l.getposition();
  Position lastpos = l.getlastposition();
  fprintf(
    stderr, "eta: \u001b[31merror in file: %s:%zu:%zu\033[0m\n",
    l.getfilename().c_str(), lastpos.row + 1, lastpos.cursor - lastpos.linebeg
  );
  fprintf(stderr, "%zu | %s\n", lastpos.row + 1, l.getln().c_str());
  fprintf(
    stderr, "%*s%*s   \u001b[31m%s\033[0m\n",
    static_cast<int>(std::floor(std::log10(lastpos.row + 1)) + 1), "",
    static_cast<int>(lastpos.linebeg - lastpos.cursor), "",
    std::string(pos.cursor - lastpos.cursor, '^').c_str()
  );
  fprintf(
    stderr, "%*s%*s   \u001b[31m%s\033[0m\n",
    static_cast<int>(std::floor(std::log10(lastpos.row + 1)) + 1), "",
    static_cast<int>(lastpos.linebeg - lastpos.cursor), "", error.c_str()
  );
  return nullptr;
}

auto logerrp(const Lexer& l, const std::string& error) -> FunctionPrototypeRef {
  logerr(l, error);
  return nullptr;
}
