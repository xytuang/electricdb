#include "electricdb/execution/vector/nullmask.h"

#include <cassert>
#include <cstring>

namespace electricdb {
NullMask::NullMask(Arena &arena, uint32_t capacity) {
#ifndef NDEBUG
	capacity_ = capacity;
#endif
	byte_count_ = (capacity + 7) / 8;
	bits_ = reinterpret_cast<uint8_t *>(arena.Allocate(byte_count_, alignof(uint8_t)));

	/** Default state is NOT NULL ie. 0 represents not null */
	std::memset(bits_, 0, byte_count_);
}

bool NullMask::IsNull(uint32_t idx) const noexcept {
/**
 * idx >> 3 tells us which byte we are lookng at in the array
 * idx & 7 gives us the lower 3 bits_ of the idx
 */
#ifndef NDEBUG
	assert(idx < capacity_);
#endif
	return bits_[idx >> 3] & (1u << (idx & 7));
}

void NullMask::SetNull(uint32_t idx) noexcept {
#ifndef NDEBUG
	assert(idx < capacity_);
#endif
	bits_[idx >> 3] |= (1u << (idx & 7));
}

void NullMask::ClearNull(uint32_t idx) noexcept {
#ifndef NDEBUG
	assert(idx < capacity_);
#endif
	bits_[idx >> 3] &= ~(1u << (idx & 7));
}

void NullMask::Reset() noexcept {
	std::memset(bits_, 0, byte_count_);
}
} // namespace electricdb