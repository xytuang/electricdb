#pragma once

#include "electricdb/execution/expressions/expression.h"
#include "electricdb/util/arena.h"

namespace electricdb {

/**
 * @brief Class for not (boolean)
 *
 */
class NotExpr final : public Expression {
  public:
	NotExpr(Expression *child);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	Expression *child_;
};

/**
 * @brief A not operator used in conjunction with electricdb/execution/expressions/type_dispatch.h
 *
 */
struct NotOp {
	template <typename T>
	static inline T Apply(T v) = delete;
};

template <>
inline bool NotOp::Apply<bool>(bool v) {
	return !v;
}

/**
 * @brief Class for negation ie. something like -x
 *
 */
class NegateExpr final : public Expression {
  public:
	NegateExpr(Expression *child);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	Expression *child_;
};

/**
 * @brief A negation operator used in conjunction with
 * electricdb/execution/expressions/type_dispatch.h
 *
 */
struct NegateOp {
	template <typename T>
	static inline T Apply(T v) {
		return -v;
	}
};
} // namespace electricdb