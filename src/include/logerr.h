#ifndef __ETA_LANG_LOGERR_H
#define __ETA_LANG_LOGERR_H

#include <cstdio>
#include <string>
#include "ast.h"
#include "lexer.h"

auto logerr(const Lexer& l, const std::string& error) -> ExpressionRef;
auto logerrp(const Lexer& l, const std::string& error) -> FunctionPrototypeRef;

#endif
