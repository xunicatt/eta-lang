#include <logerr.h>

auto logerr(const std::string& error) -> ExpressionRef {
  fprintf(stderr, "eta: error: %s\n", error.c_str());
  return nullptr;
}

auto logerrp(const std::string& error) -> FunctionPrototypeRef {
  logerr(error);
  return nullptr;
}
