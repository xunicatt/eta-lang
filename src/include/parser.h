#ifndef __ETA_LANG_PARSER_H
#define __ETA_LANG_PARSER_H

#include "ast.h"
#include "lexer.h"

auto ParseExpression(Lexer &l) -> ExpressionRef;
auto ParsePrimary(Lexer &l) -> ExpressionRef;
auto ParseParen(Lexer &l) -> ExpressionRef;
auto ParseIdentifier(Lexer &l) -> ExpressionRef;
auto ParseNumber(Lexer &l) -> ExpressionRef;
auto ParseBinary(Lexer &l, int opprec, ExpressionRef lhs) -> ExpressionRef;
auto ParseVariable(Lexer &l) -> ExpressionRef;
auto ParseRoot(Lexer &l) -> ExpressionRef;

#endif
