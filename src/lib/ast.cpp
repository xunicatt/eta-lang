#include <ast.h>

Number::Number(NumberVariant value, NumberType type, NumberWidth width) :
    value(value), type(type), width(width) {
}

Variable::Variable(const std::string& name) : name(name) {
}

BinaryExpression::BinaryExpression(
  Token op, ExpressionRef lhs, ExpressionRef rhs
) :
    lhs(std::move(lhs)), rhs(std::move(rhs)), op(op) {
}

FunctionCall::FunctionCall(
  const std::string& name, std::vector<ExpressionRef> args
) :
    name(name), args(std::move(args)) {
}

FunctionPrototype::FunctionPrototype(
  const std::string& name, std::vector<ExpressionRef> args
) :
    name(name), args(std::move(args)) {
}

auto FunctionPrototype::getname() const -> const std::string& {
  return name;
}

Function::Function(FunctionPrototypeRef prototype, ExpressionRef body) :
    prototype(std::move(prototype)), body(std::move(body)) {
}
