#include "electricdb/execution/expressions/unary_expression.h"

#include "electricdb/common/constants.h"
#include "electricdb/execution/expressions/type_dispatch.h"

namespace electricdb {
NotExpr::NotExpr(Expression *child) : child_(child) {}

void NotExpr::Execute(ExecutionContext &ctx, Vector &result) {
	/** Prepare child vector */
	auto &child_vec_ = ctx.GetTempVector(child_->Type());

	/** Evaluate child expression */
	child_->Execute(ctx, child_vec_);

#ifndef NDEBUG
	assert(result.Type() == LogicalType::BOOL);
#endif
    result.SetSize(child_vec_.Size());
	UnaryBoolDispatch<NotOp>(ctx, result, child_vec_);
}

LogicalType NotExpr::Type() const {
	return LogicalType::BOOL;
}

NegateExpr::NegateExpr(Expression *child) : child_(child) {}

void NegateExpr::Execute(ExecutionContext &ctx, Vector &result) {
	auto &child_vec_ = ctx.GetTempVector(child_->Type());

	child_->Execute(ctx, child_vec_);

#ifndef NDEBUG
	auto t = result.Type();
	assert(t == LogicalType::INT32 || t == LogicalType::INT64 || t == LogicalType::FLOAT ||
		   t == LogicalType::DOUBLE);
#endif
	result.SetSize(child_vec_.Size());
	UnaryTypeDispatch<NegateOp>(ctx, result, child_vec_);
}

LogicalType NegateExpr::Type() const {
	return child_->Type();
}

} // namespace electricdb