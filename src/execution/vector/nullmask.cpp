#include "electricdb/execution/vector/nullmask.h"

#include <cstring>

namespace electricdb {
NullMask::NullMask(Arena &arena, uint32_t capacity) {
	byte_count = (capacity + 7) / 8;
	bits = reinterpret_cast<uint8_t *>(arena.allocate(byte_count, alignof(uint8_t)));

	/** Default state is NOT NULL ie. 0 represents not null */
	std::memset(bits, 0, byte_count);
}

bool NullMask::IsNull(uint32_t idx) const noexcept {
	/**
	 * idx >> 3 tells us which byte we are lookng at in the array
	 * idx & 7 gives us the lower 3 bits of the idx
	 */
	return bits[idx >> 3] & (1u << (idx & 7));
}

void NullMask::SetNull(uint32_t idx) {
	bits[idx >> 3] |= (1u << (idx & 7));
}

void NullMask::ClearNull(uint32_t idx) {
	bits[idx >> 3] &= ~(1u << (idx & 7));
}

void NullMask::Reset() {
	std::memset(bits, 0, byte_count);
}
} // namespace electricdb