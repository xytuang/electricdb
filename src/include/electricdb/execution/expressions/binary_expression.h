#pragma once

#include "electricdb/execution/expressions/expression.h"

namespace electricdb {

/**
 * @brief Class for addition
 *
 */
class AddExpr final : public Expression {
  public:
	AddExpr(Expression *left, Expression *right);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	Expression *left_;
	Expression *right_;
};

/**
 * @brief An add operator used in conjunction with electricdb/execution/expressions/type_dispatch.h
 *
 */
struct AddOp {
	template <typename T>
	static inline T Apply(T lhs, T rhs) {
		return lhs + rhs;
	}
};

/**
 * @brief Class for subtraction
 *
 */
class SubExpr final : public Expression {
  public:
	SubExpr(Expression *left, Expression *right);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	Expression *left_;
	Expression *right_;
};

/**
 * @brief A subtraction operator used in conjunction with
 * electricdb/execution/expressions/type_dispatch.h
 *
 */
struct SubOp {
	template <typename T>
	static inline T Apply(T lhs, T rhs) {
		return lhs - rhs;
	}
};

/**
 * @brief Class for multiplication
 *
 */
class MultExpr final : public Expression {
  public:
	MultExpr(Expression *left, Expression *right);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	Expression *left_;
	Expression *right_;
};

/**
 * @brief A mult operator used in conjunction with electricdb/execution/expressions/type_dispatch.h
 *
 */
struct MultOp {
	template <typename T>
	static inline T Apply(T lhs, T rhs) {
		return lhs * rhs;
	}
};

/**
 * @brief Class for division
 *
 */
class DivExpr final : public Expression {
  public:
	DivExpr(Expression *left, Expression *right);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	Expression *left_;
	Expression *right_;
};

/**
 * @brief An add operator used in conjunction with electricdb/execution/expressions/type_dispatch.h
 *
 */
struct DivOp {
	template <typename T>
	static inline T Apply(T lhs, T rhs) {
		return lhs / rhs;
	}
};

} // namespace electricdb