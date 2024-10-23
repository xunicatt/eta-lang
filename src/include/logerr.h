#ifndef __ETA_LANG_LOGERR_H
#define __ETA_LANG_LOGERR_H

#include <cstdio>
#include <string>
#include "ast.h"

auto logerr(const std::string& error) -> ExpressionRef;
auto logerrp(const std::string& error) -> FunctionPrototypeRef;

#endif
