#pragma once

#include "electricdb/util/arena.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace electricdb {

using sel_t = uint32_t;
using idx_t = uint32_t;

class SelectionVector {
  public:
	/** Constructors */

	/**
	 * @brief Construct a new Selection Vector with identity mapping, no selection applied
	 *
	 */
	SelectionVector() noexcept;

	/**
	 * @brief Allocate storage for up to capacity indicies
	 *
	 * @param arena Arena allocator
	 * @param capacity Maximum number of indices to store
	 */
	SelectionVector(Arena &arena, idx_t capacity);

	/**
	 * @brief Reset to identity mapping (logical clear, no free)
	 *
	 */
	void Reset() noexcept;

	/**
	 * @brief Make this selection vector reference another one
	 *
	 * @param other
	 */
	void Reference(const SelectionVector &other) noexcept;

	/**
	 * @brief Maps from logical index to physical row index
	 *
	 * @param i Logical index to look up
	 * @return idx_t Physical index
	 */
	inline idx_t Get(idx_t i) const noexcept {
		if (data_)
			return data_[i];
		return i;
	}

	/**
	 * @brief Unsafe version of get (no identity fallback)
	 *
	 * @param i Logical index to look up
	 * @return idx_t Physical index
	 */
	inline idx_t GetUnsafe(idx_t i) const noexcept { return data_[i]; }

	/**
	 * @brief Pointer to underlying index array (or nullptr)
	 *
	 * @return sel_t* Pointer to index array
	 */
	inline sel_t *Data() noexcept { return data_; }

	inline const sel_t *Data() const noexcept { return data_; }

	inline sel_t Size() const noexcept { return capacity_; }

	/**
	 * @brief Checks if there is an identity mapping
	 *
	 * @return true if data_ == nullptr
	 * @return false otherwise
	 */
	inline bool IsIdentity() const noexcept { return data_ == nullptr; }

	/**
	 * @brief Set ith entry to row index `row`
	 *
	 * @param i Logical index to update
	 * @param row New value at logical index `i`
	 */
	inline void Set(idx_t i, idx_t row) noexcept { data_[i] = row; }

	/**
	 * @brief Swap two entries (used by sort)
	 *
	 * @param a Logical index to swap
	 * @param b Another logical index to swap
	 */
	void Swap(idx_t a, idx_t b) noexcept { std::swap(data_[a], data_[b]); }

	/**
	 * @brief Store rows not selected by src inside dst
	 *
	 * @param src SelectionVector to lookup
	 * @param dst SelectionVector to contain all rows not selected by `src`
	 * @param input_count Range over which to look for
	 * @param src_count Number of rows in `src`
	 * @return idx_t
	 */
	static idx_t Invert(const SelectionVector &src, SelectionVector &dst, idx_t input_count,
						idx_t src_count);

  private:
	/** @brief Stores index array. If nullptr, use identity mapping */
	sel_t *data_;
	/** @brief Maximum number of row indices held by this selection vector */
	idx_t capacity_;
};

} // namespace electricdb
