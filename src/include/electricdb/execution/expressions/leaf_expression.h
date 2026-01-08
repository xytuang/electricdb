#pragma once

#include "electricdb/common/types.h"
#include "electricdb/execution/expressions/expression.h"

namespace electricdb {

/**
 * @brief Get the values specified at column_idx
 *
 */
class ColumnExpr final : public Expression {
  public:
	ColumnExpr(uint32_t column_idx, LogicalType type);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	/** @brief Index to read from */
	uint32_t column_idx_;
	LogicalType type_;
};

class ConstantExpr final : public Expression {
  public:
	ConstantExpr(const Value &value);

	void Execute(ExecutionContext &ctx, Vector &result) override;
	LogicalType Type() const override;

  private:
	/** The constant value */
	Value value_;
};

} // namespace electricdb
