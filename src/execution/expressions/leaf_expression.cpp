#include "electricdb/execution/expressions/leaf_expression.h"

#include "electricdb/execution/expressions/type_dispatch.h"

namespace electricdb {
ColumnExpr::ColumnExpr(uint32_t column_idx, LogicalType type)
	: column_idx_(column_idx), type_(type) {}

void ColumnExpr::Execute(ExecutionContext &ctx, Vector &result) {

	const auto &input = *ctx.Input();
	const Vector &col = input[column_idx_];
	result.Reference(col);
}

LogicalType ColumnExpr::Type() const {
	return type_;
}

ConstantExpr::ConstantExpr(const Value &value) : value_(value) {}

void ConstantExpr::Execute(ExecutionContext &ctx, Vector &result) {
	const idx_t n_ = result.Size();
	auto sel_ = ctx.Selection();

	if (value_.IsNull()) {
		for (idx_t i = 0; i < n_; i++) {
			idx_t row = sel_ ? sel_->Get(i) : i;
			result.SetNull(row);
		}
		return;
	}
	ConstantDispatch(ctx, result, value_);
}

LogicalType ConstantExpr::Type() const {
	return value_.GetType();
}
} // namespace electricdb