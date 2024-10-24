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
  NTNEGINT,
  NTPOSINT,
  NTNEGFLT,
  NTPOSFLT
};

using NumberVariant = std::variant<uint64_t, double>;

class Number : public Expression {
public:
  Number(const NumberVariant value, const NumberType type);

private:
  const NumberVariant value;
  const NumberType type;
};

enum VariableType : uint8_t {
  VTI8,
  VTI16,
  VTI32,
  VTI64,
  VTU8,
  VTU16,
  VTU32,
  VTU64,
  VTF32,
  VTF64,
  VTBOOL,
  VTSTRING,
  VTSTRUCT
};

enum VariableKind : uint8_t {
  VKMUT,
  VKCONST,
};

class Variable : public Expression {
public:
  Variable(
    const std::string& name, const VariableType type, const VariableKind kind,
    const std::string& customstruct = ""
  );

private:
  const std::string name;
  const VariableType type;
  const VariableKind kind;
  const std::string& customstruct;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(const Token op, ExpressionRef lhs, ExpressionRef rhs);

private:
  ExpressionRef lhs;
  ExpressionRef rhs;
  Token op;
};

class FunctionCall : public Expression {
public:
  FunctionCall(const std::string& name, const std::vector<ExpressionRef>& args);

private:
  const std::string& name;
  const std::vector<ExpressionRef>& args;
};

class FunctionPrototype : public Expression {
public:
  FunctionPrototype(
    const std::string& name, const std::vector<ExpressionRef>& args
  );
  auto getname() const -> const std::string&;

private:
  const std::string& name;
  const std::vector<ExpressionRef>& args;
};

using FunctionPrototypeRef = std::unique_ptr<FunctionPrototype>;

class Function : public Expression {
public:
  Function(const FunctionPrototypeRef& prototype, const ExpressionRef& body);

private:
  const FunctionPrototypeRef& prototype;
  const ExpressionRef& body;
};

#endif
