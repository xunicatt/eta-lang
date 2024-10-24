#include <ast.h>

Number::Number(const NumberVariant value, const NumberType type) :
    value(value), type(type) {
}

Variable::Variable(
  const std::string& name, const VariableType type, const VariableKind kind,
  const std::string& customstruct
) :
    name(name), type(type), kind(kind), customstruct(customstruct) {
}

BinaryExpression::BinaryExpression(
  Token op, ExpressionRef lhs, ExpressionRef rhs
) :
    lhs(std::move(lhs)), rhs(std::move(rhs)), op(op) {
}

FunctionCall::FunctionCall(
  const std::string& name, const std::vector<ExpressionRef>& args
) :
    name(name), args(std::move(args)) {
}

FunctionPrototype::FunctionPrototype(
  const std::string& name, const std::vector<ExpressionRef>& args
) :
    name(name), args(std::move(args)) {
}

auto FunctionPrototype::getname() const -> const std::string& {
  return name;
}

Function::Function(
  const FunctionPrototypeRef& prototype, const ExpressionRef& body
) :
    prototype(std::move(prototype)), body(std::move(body)) {
}
