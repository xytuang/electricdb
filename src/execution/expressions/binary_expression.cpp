#include "electricdb/execution/expressions/binary_expression.h"

#include "electricdb/common/constants.h"
#include "electricdb/execution/expressions/type_dispatch.h"

namespace electricdb {
AddExpr::AddExpr(Expression *left, Expression *right) : left_(left), right_(right) {}

void AddExpr::Execute(ExecutionContext &ctx, Vector &result) {
	/** Prepare child vectors */
	auto &left_vec_ = ctx.GetTempVector(left_->Type());
	left_vec_.SetSize(result.Size());

	auto &right_vec_ = ctx.GetTempVector(right_->Type());
	right_vec_.SetSize(result.Size());

	/** Evaluate child expressions */
	left_->Execute(ctx, left_vec_);
	right_->Execute(ctx, right_vec_);

#ifndef NDEBUG
	assert(result.Type() == LogicalType::INT32 || result.Type() == LogicalType::INT64 ||
		   result.Type() == LogicalType::FLOAT || result.Type() == LogicalType::DOUBLE);
#endif

	BinaryTypeDispatch<AddOp>(ctx, result, left_vec_, right_vec_);
}

/**
 * @brief Assume left and right have the same type for now
 *
 * @return LogicalType
 */
LogicalType AddExpr::Type() const {
	if (!left_)
		return right_->Type();
	if (!right_)
		return left_->Type();

	return left_->Type();
}

SubExpr::SubExpr(Expression *left, Expression *right) : left_(left), right_(right) {}

void SubExpr::Execute(ExecutionContext &ctx, Vector &result) {
	/** Prepare child vectors */
	auto &left_vec_ = ctx.GetTempVector(left_->Type());
	left_vec_.SetSize(result.Size());

	auto &right_vec_ = ctx.GetTempVector(right_->Type());
	right_vec_.SetSize(result.Size());

	/** Evaluate child expressions */
	left_->Execute(ctx, left_vec_);
	right_->Execute(ctx, right_vec_);

#ifndef NDEBUG
	assert(result.Type() == LogicalType::INT32 || result.Type() == LogicalType::INT64 ||
		   result.Type() == LogicalType::FLOAT || result.Type() == LogicalType::DOUBLE);
#endif

	BinaryTypeDispatch<SubOp>(ctx, result, left_vec_, right_vec_);
}

/**
 * @brief Assume left and right have the same type for now
 *
 * @return LogicalType
 */
LogicalType SubExpr::Type() const {
	if (!left_)
		return right_->Type();
	if (!right_)
		return left_->Type();

	return left_->Type();
}

MultExpr::MultExpr(Expression *left, Expression *right) : left_(left), right_(right) {}

void MultExpr::Execute(ExecutionContext &ctx, Vector &result) {
	/** Prepare child vectors */
	auto &left_vec_ = ctx.GetTempVector(left_->Type());
	left_vec_.SetSize(result.Size());

	auto &right_vec_ = ctx.GetTempVector(right_->Type());
	right_vec_.SetSize(result.Size());

	/** Evaluate child expressions */
	left_->Execute(ctx, left_vec_);
	right_->Execute(ctx, right_vec_);

#ifndef NDEBUG
	assert(result.Type() == LogicalType::INT32 || result.Type() == LogicalType::INT64 ||
		   result.Type() == LogicalType::FLOAT || result.Type() == LogicalType::DOUBLE);
#endif

	BinaryTypeDispatch<MultOp>(ctx, result, left_vec_, right_vec_);
}

/**
 * @brief Assume left and right have the same type for now
 *
 * @return LogicalType
 */
LogicalType MultExpr::Type() const {
	if (!left_)
		return right_->Type();
	if (!right_)
		return left_->Type();

	return left_->Type();
}

DivExpr::DivExpr(Expression *left, Expression *right) : left_(left), right_(right) {}

void DivExpr::Execute(ExecutionContext &ctx, Vector &result) {
	/** Prepare child vectors */
	auto &left_vec_ = ctx.GetTempVector(left_->Type());
	left_vec_.SetSize(result.Size());

	auto &right_vec_ = ctx.GetTempVector(right_->Type());
	right_vec_.SetSize(result.Size());

	/** Evaluate child expressions */
	left_->Execute(ctx, left_vec_);
	right_->Execute(ctx, right_vec_);

#ifndef NDEBUG
	assert(result.Type() == LogicalType::INT32 || result.Type() == LogicalType::INT64 ||
		   result.Type() == LogicalType::FLOAT || result.Type() == LogicalType::DOUBLE);
#endif

	BinaryTypeDispatch<DivOp>(ctx, result, left_vec_, right_vec_);
}

/**
 * @brief Assume left and right have the same type for now
 *
 * @return LogicalType
 */
LogicalType DivExpr::Type() const {
	if (!left_)
		return right_->Type();
	if (!right_)
		return left_->Type();

	return left_->Type();
}
} // namespace electricdb