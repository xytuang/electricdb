#pragma once

#include "electricdb/common/types.h"
#include "electricdb/execution/vector/nullmask.h"
#include "electricdb/execution/vector/selection_vector.h"
#include "electricdb/util/arena.h"

#include <memory>

namespace electricdb {

class Vector {
  public:
	/**
	 * @brief Construct a new Vector object
	 *
	 * @param type
	 * @param capacity
	 */
	Vector(LogicalType type, uint32_t capacity, Arena &arena);
	~Vector() = default;

	/** @brief Disable copy constructor */
	Vector(const Vector &) = delete;

	/** @brief Disable copy assignment  */
	Vector &operator=(const Vector &) = delete;

	/** @brief Custom move constructor */
	Vector(Vector &&) noexcept;

	/** @brief Custom move assignment */
	auto operator=(Vector &&) noexcept -> Vector &;

	/**
	 * @brief Functions below are for getting metadata
	 *
	 */
	/** @brief Return type of each element in this vector */
	LogicalType Type() const noexcept;

	/** @brief Returns number of elements in this vector */
	uint32_t Size() const noexcept;

	/** @brief Returns maximum number of elements that can be stored in this vector */
	uint32_t Capacity() const noexcept;

	/** @brief Set the number of elements in this vector.
	 * Note: This function does not touch null state and HasNulls may
	 * indicate the wrong state if there are no nulls left after resizing
	 */
	void SetSize(uint32_t size);

	/**
	 * @brief Functions below are for data access
	 *
	 */
	/** @brief Write access to data */
	template <typename T>
	T *Data() {
#ifndef NDEBUG
		assert(TypeMatches<T>(logical_type_));
#endif
		return reinterpret_cast<T *>(data_);
	}

	/** @brief Guarantee pointer will not be modified */
	template <typename T>
	const T *Data() const {
#ifndef NDEBUG
		assert(TypeMatches<T>(logical_type_));
#endif
		return reinterpret_cast<const T *>(data_);
	}

	/**
	 * @brief Functions below are for null handling
	 *
	 */

	/**
	 * @brief Check if this vector has null values
	 *
	 * @return true if there are null values in this vector
	 * @return false if vector has no null values
	 */
	bool HasNulls() const noexcept;
	/**
	 * @brief Checks if element at specified index is null
	 *
	 * @param idx Index to check
	 * @return true if element at idx is null
	 * @return false otherwise
	 */
	bool IsNull(uint32_t idx) const noexcept;
	/**
	 * @brief Sets index in vector to null
	 *
	 * @param idx Index to update
	 */
	void SetNull(uint32_t idx);
	/**
	 * @brief Clears null if present at idx
	 *
	 * @param idx Index that contains element and requires null clearing
	 */
	void ClearNull(uint32_t idx);

	/**
	 * @brief Checks if there is a selection vector ie. filter applied to this vector
	 *
	 * @return true if there is a selection vector
	 * @return false otherwise
	 */
	bool HasSelection() const noexcept;

	/**
	 * @brief Returns read only access to the Selection Vector applied to this vector
	 *
	 * @return const SelectionVector*
	 */
	const SelectionVector *Selection() const noexcept;

	/**
	 * @brief Set a selection vector for this vector
	 *
	 * @param sel
	 */
	void SetSelection(const SelectionVector *sel);

	/**
	 * @brief Remove selection vector from this vector
	 *
	 */
	void ClearSelection();

	void Reset();

  private:
	LogicalType logical_type_;
	uint32_t size_;
	uint32_t capacity_;
	void *data_;
	uint32_t null_count_;
	std::unique_ptr<NullMask> nulls_;
	/** @brief  selection_ is a non owning pointer. The referenced selection vector must outlive the
	 * Vector*/
	const SelectionVector *selection_;
};
} // namespace electricdb
