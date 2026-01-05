#pragma once

#include <cstddef>
#include <cstdint>

namespace electricdb {
class NullMask {
	public:
		explicit NullMask(uint32_t capacity);
		bool IsNull(uint32_t idx) const noexcept;
		void SetNull(uint32_t idx);
		void ClearNull(uint32_t idx);
		void Reset();
	private:
		uint8_t *bits;
};
} // namespace electricdb
