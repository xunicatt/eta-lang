#ifndef __ETA_LANG_AST_H
#define __ETA_LANG_AST_H

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include "tokens.h"

class Expression {
public:
  virtual ~Expression() = default;
};

using ExpressionRef = std::unique_ptr<Expression>;

enum NumberType : uint8_t {
  UNSIGNED,
  SIGNED,
  FLOAT,
  DOUBLE,
};

enum NumberWidth : uint8_t {
  S8,
  S16,
  S32,
  S64
};

using NumberVariant = std::variant<int64_t, uint64_t, float, double>;

class Number : public Expression {
public:
  Number(NumberVariant value, NumberType type, NumberWidth width);

private:
  NumberVariant value;
  NumberType type;
  NumberWidth width;
};

class Variable : public Expression {
public:
  Variable(const std::string& name);

private:
  const std::string name;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(Token op, ExpressionRef lhs, ExpressionRef rhs);

private:
  ExpressionRef lhs;
  ExpressionRef rhs;
  Token op;
};

class FunctionCall : public Expression {
public:
  FunctionCall(const std::string& name, std::vector<ExpressionRef> args);

private:
  std::string name;
  std::vector<ExpressionRef> args;
};

class FunctionPrototype : public Expression {
public:
  FunctionPrototype(const std::string& name, std::vector<ExpressionRef> args);
  auto getname() const -> const std::string&;

private:
  std::string name;
  std::vector<ExpressionRef> args;
};

using FunctionPrototypeRef = std::unique_ptr<FunctionPrototype>;

class Function : public Expression {
public:
  Function(FunctionPrototypeRef prototype, ExpressionRef body);

private:
  FunctionPrototypeRef prototype;
  ExpressionRef body;
};

#endif
