#pragma once

#include "electricdb/util/arena.h"

#include <cstddef>
#include <cstdint>

namespace electricdb {
class NullMask {
  public:
	explicit NullMask(Arena &arena, uint32_t capacity);
	bool IsNull(uint32_t idx) const noexcept;
	void SetNull(uint32_t idx) noexcept;
	void ClearNull(uint32_t idx) noexcept;
	void Reset() noexcept;

  private:
	uint8_t *bits;
	uint32_t byte_count;
	uint32_t capacity;
};
} // namespace electricdb
