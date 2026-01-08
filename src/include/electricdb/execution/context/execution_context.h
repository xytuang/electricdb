#pragma once

#include "electricdb/common/constants.h"
#include "electricdb/execution/vector/selection_vector.h"
#include "electricdb/execution/vector/vector.h"
#include "electricdb/util/arena.h"

#include <vector>
#include <deque>

namespace electricdb {

/**
 * @brief ExecutionContext represents thread-local state for execution.
 *
 * One ExecutionContext exists per worker thread.
 * It owns all temporary memory used during expression evaluation.
 */
class ExecutionContext {
  public:
	explicit ExecutionContext(uint32_t default_vector_size = DEFAULT_VECTOR_SIZE)
		: arena_(), default_vector_size_(default_vector_size) {}

	/** @brief Reset all ephemeral memory */
	void Reset() {
		arena_.Reset();
		scratch_vectors_.clear();
		input_ = nullptr;
		selection_ = nullptr;
	}

	/** @brief Arena access */
	Arena &Arena() { return arena_; }

	/** @brief Default vector size (batch size) */
	uint32_t VectorSize() const { return default_vector_size_; }

	/** @brief Set input chunk for ColumnExpr */
	void SetInput(const std::vector<Vector> *input) { input_ = input; }

	const std::vector<Vector> *Input() const { return input_; }

	/** @brief Selection vector handling */
	void SetSelection(const SelectionVector *sel) { selection_ = sel; }

	/** @brief Return selection vector */
	const SelectionVector *Selection() const { return selection_; }

	/**
	 * @brief Get index to a temporary vector owned by this context
	 */
	Vector &GetTempVector(LogicalType type) {
		scratch_vectors_.emplace_back(type, default_vector_size_, arena_);
		return scratch_vectors_.back();
	}

  private:
	class Arena arena_;

	uint32_t default_vector_size_;

	/** @brief Scratch vectors for intermediate expression results */
	std::deque<Vector> scratch_vectors_;

	/** @brief Pointer to current input chunk */
	const std::vector<Vector> *input_ = nullptr;

	/** @brief Current selection vector */
	const SelectionVector *selection_ = nullptr;
};

} // namespace electricdb
