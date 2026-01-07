#include "electricdb/util/arena.h"

#include <cassert>
#include <cstddef>
#include <cstdlib>

namespace electricdb {
/**
 * @brief Align ptr upwards to alignment
 *
 * @param ptr ptr to align
 * @param alignment amount to align by
 * @return uintptr_t Pointer to aligned memory
 */
inline uintptr_t align_up(uintptr_t ptr, size_t alignment) {
	const uintptr_t mask = alignment - 1;
	return (ptr + mask) & ~mask;
}

/**
 * @brief Construct a new Arena
 *
 * @param block_size Size of one block in the arena
 */
Arena::Arena(size_t block_size) : block_size_(block_size) {
	assert((block_size_ & (block_size_ - 1)) == 0 && "Block size must be a power of two");
}

/**
 * @brief Destroy the Arena, freeing all allocated memory in each block
 *
 */
Arena::~Arena() {
	for (auto block : blocks_)
		std::free(block.data);
}

/**
 * @brief Construct a new Arena from existing Arena object
 *
 */
Arena::Arena(Arena &&other) noexcept
	: blocks_(std::move(other.blocks_)), block_size_(other.block_size_) {
	other.blocks_
			.clear(); /** Blocks in other Arena have been moved over, clear references to them */
}

/**
 * @brief Move blocks from other Arena to this ie. this Arena already exists (different from move
 * constructor)
 *
 * @return Arena::Arena New Arena object
 */
auto Arena::operator=(Arena &&other) noexcept -> Arena & {
	if (this != &other) {
		for (auto block : blocks_)
			std::free(block.data);
		block_size_ = other.block_size_;
		blocks_ = std::move(other.blocks_);
		other.blocks_.clear();
	}

	return *this;
}

/**
 * @brief Allocate a block of size with alignment
 *
 * @param size Amount of bytes to allocate
 * @param alignment Align handle to this value
 * @return void* pointer to aligned region
 */
void *Arena::Allocate(size_t size, size_t alignment) {
	assert(alignment && (alignment & (alignment - 1)) == 0);

	if (blocks_.empty()) {
		blocks_.push_back({reinterpret_cast<uint8_t *>(std::malloc(block_size_)), block_size_, 0});
		assert(blocks_.back().data);
	}

	Block *block = &blocks_.back();
	uintptr_t base = reinterpret_cast<uintptr_t>(block->data);
	uintptr_t current = base + block->used;
	uintptr_t aligned = align_up(current, alignment);

	size_t padding = aligned - current;
	size_t total = padding + size;

	/** Check if total amount of size needed exceeds currently available capacity */
	if (block->used + total > block->size) {
		size_t new_block_size = std::max(block_size_, size + alignment);
		blocks_.push_back(
				{reinterpret_cast<uint8_t *>(std::malloc(new_block_size)), new_block_size, 0});

		assert(blocks_.back().data);

		block = &blocks_.back();
		base = reinterpret_cast<uintptr_t>(block->data);
		aligned = align_up(base, alignment);
		padding = aligned - current;
		total = padding + size;
	}

	block->used += total;

	return reinterpret_cast<void *>(aligned);
}

/**
 * @brief Reset this arena, freeing all blocks except for the very first block
 *
 */
void Arena::Reset() {
	for (size_t i = 1; i < blocks_.size(); i++)
		std::free(blocks_[i].data);

	if (!blocks_.empty()) {
		blocks_[0].used = 0;
		blocks_.resize(1);
	}
}

size_t Arena::bytes_used() const noexcept {
	size_t used = 0;

	for (auto block : blocks_) {
		used += block.used;
	}

	return used;
}

size_t Arena::bytes_reserved() const noexcept {
	size_t total = 0;

	for (auto block : blocks_) {
		total += block.size;
	}

	return total;
}

} // namespace electricdb