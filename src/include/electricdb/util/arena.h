#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace electricdb {
class Arena {
  public:
	explicit Arena(size_t block_size = kDefaultBlockSize);
	~Arena();

	/** @brief Disable copy constructor */
	Arena(const Arena &) = delete;

	/** @brief Disable copy assignment  */
	Arena &operator=(const Arena &) = delete;

	/** @brief Custom move constructor */
	Arena(Arena &&) noexcept;

	/** @brief Custom move assignment */
	auto operator=(Arena &&) noexcept -> Arena &;

	/**
	 * @brief Allocate raw memory with alignment
	 *
	 * @param size Number of bytes to allocate
	 * @param alignment Alignment of memory region to allocate
	 * @return void* Pointer to newly allocated memory region
	 */
	void *allocate(size_t size, size_t alignment = alignof(std::max_align_t));

	/**
	 * @brief Typed allocation helper
	 *
	 * @tparam T type to allocate
	 * @param count Number of T objects this memory region will store
	 * @return T* Pointer to newly allocated region
	 */
	template <typename T>
	T *allocate(size_t count = 1) {
		return reinterpret_cast<T *>(allocate(count * sizeof(T), alignof(T)));
	}

	/**
	 * @brief Reset arena, invalidating all allocations
	 *
	 */
	void reset();

	size_t bytes_used() const noexcept;
	size_t bytes_reserved() const noexcept;

  private:
	/**
	 * @brief Block struct that represents one contiguous region
	 *
	 */
	struct Block {
		uint8_t *data;
		size_t size;
		size_t used;
	};

	static constexpr size_t kDefaultBlockSize = 1 << 20; /** 1 MB */
	std::vector<Block> blocks_;
	size_t block_size_;
};
} // namespace electricdb