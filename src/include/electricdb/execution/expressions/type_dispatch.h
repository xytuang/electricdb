#pragma once

#include "electricdb/common/types.h"
#include "electricdb/execution/vector/vector.h"

namespace electricdb {
/**
 * @brief Dispatches a unary type operation over a vector based on LogicalType
 *
 * @tparam OP must define template <typename T> static inline T Apply(T v)
 * @param out
 * @param in
 */
template <typename OP>
inline void UnaryTypeDispatch(ExecutionContext &ctx, Vector &out, const Vector &in) {

	auto sel = ctx.Selection();
	idx_t n = sel ? sel->Size() : out.Size();

	out.ClearNulls();

	switch (out.Type()) {
	case LogicalType::INT32: {
		auto dst = out.Data<int32_t>();
		auto src = in.Data<int32_t>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (in.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<int32_t>(src[row]);
			}
		}
		break;
	}
	case LogicalType::INT64: {
		auto dst = out.Data<int64_t>();
		auto src = in.Data<int64_t>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (in.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<int64_t>(src[row]);
			}
		}
		break;
	}
	case LogicalType::FLOAT: {
		auto dst = out.Data<float>();
		auto src = in.Data<float>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (in.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<float>(src[row]);
			}
		}
		break;
	}
	case LogicalType::DOUBLE: {
		auto dst = out.Data<double>();
		auto src = in.Data<double>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (in.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<double>(src[row]);
			}
		}
		break;
	}
	default:
		__builtin_unreachable();
	}
}

/**
 * @brief Dispatches unary boolean operation over a vector based on LogicalType
 *
 * @tparam OP
 * @param out
 * @param in
 */
template <typename OP>
inline void UnaryBoolDispatch(ExecutionContext &ctx, Vector &out, const Vector &in) {
#ifndef NDEBUG
	assert(out.Type() == LogicalType::BOOL);
	assert(in.Type() == LogicalType::BOOL);
#endif

	auto sel = ctx.Selection();
	idx_t n = sel ? sel->Size() : out.Size();

	out.ClearNulls();

	auto dst = out.Data<bool>();
	auto src = in.Data<bool>();

	for (idx_t i = 0; i < n; i++) {
		idx_t row = sel ? sel->Get(i) : i;
		if (in.IsNull(row)) {
			out.SetNull(row);
		} else {
			dst[row] = OP::Apply(src[row]);
		}
	}
}

/**
 * @brief Dispatches a binary type operation over a vector based on LogicalType
 *
 * @tparam OP must define template <typename T> static inline T Apply(T v)
 * @param out
 * @param lhs
 * @param rhs
 */
template <typename OP>
inline void BinaryTypeDispatch(ExecutionContext &ctx, Vector &out, const Vector &lhs, const Vector &rhs) {

#ifndef NDEBUG
    assert(out.Size() == lhs.Size());
    assert(out.Size() == rhs.Size());
#endif

	auto sel = ctx.Selection();
	auto n = out.Size();

	out.ClearNulls();

	switch (out.Type()) {
	case LogicalType::INT32: {
		auto dst = out.Data<int32_t>();
		auto left = lhs.Data<int32_t>();
		auto right = rhs.Data<int32_t>();

		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (lhs.IsNull(row) || rhs.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<int32_t>(left[row], right[row]);
			}
		}
		break;
	}
	case LogicalType::INT64: {
		auto dst = out.Data<int64_t>();
		auto left = lhs.Data<int64_t>();
		auto right = rhs.Data<int64_t>();

		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (lhs.IsNull(row) || rhs.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<int64_t>(left[row], right[row]);
			}
		}
		break;
	}
	case LogicalType::FLOAT: {
		auto dst = out.Data<float>();
		auto left = lhs.Data<float>();
		auto right = rhs.Data<float>();

		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (lhs.IsNull(row) || rhs.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<float>(left[row], right[row]);
			}
		}
		break;
	}
	case LogicalType::DOUBLE: {
		auto dst = out.Data<double>();
		auto left = lhs.Data<double>();
		auto right = rhs.Data<double>();

		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
			if (lhs.IsNull(row) || rhs.IsNull(row)) {
				out.SetNull(row);
			} else {
				dst[row] = OP::template Apply<double>(left[row], right[row]);
			}
		}
		break;
	}
	default:
		__builtin_unreachable();
	}
}

inline void ConstantDispatch(ExecutionContext &ctx, Vector &out, const Value &value) {
	auto sel = ctx.Selection();
	idx_t n = sel ? sel->Size() : out.Size();

	out.ClearNulls();

	switch (value.Type()) {
	case LogicalType::INT32: {
		auto dst = out.Data<int32_t>();
		auto v = value.Get<int32_t>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
#ifndef NDEBUG
            assert(row < out.Size());
#endif
			dst[row] = v;
		}
		break;
	}
	case LogicalType::INT64: {
		auto dst = out.Data<int64_t>();
		auto v = value.Get<int64_t>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
#ifndef NDEBUG
            assert(row < out.Size());
#endif
			dst[row] = v;
		}
		break;
	}
	case LogicalType::FLOAT: {
		auto dst = out.Data<float>();
		auto v = value.Get<float>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
#ifndef NDEBUG
            assert(row < out.Size());
#endif
			dst[row] = v;
		}
		break;
	}
	case LogicalType::DOUBLE: {
		auto dst = out.Data<double>();
		auto v = value.Get<double>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
#ifndef NDEBUG
            assert(row < out.Size());
#endif
			dst[row] = v;
		}
		break;
	}
	case LogicalType::BOOL: {
		auto dst = out.Data<bool>();
		auto v = value.Get<bool>();
		for (idx_t i = 0; i < n; i++) {
			idx_t row = sel ? sel->Get(i) : i;
#ifndef NDEBUG
            assert(row < out.Size());
#endif
			dst[row] = v;
		}
		break;
	}
	default:
		__builtin_unreachable();
	}
}
} // namespace electricdb