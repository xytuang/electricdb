#pragma once

#include <cstddef>

namespace electricdb {

inline constexpr size_t kDefaultWidth = 1;

inline constexpr size_t Width() noexcept {
	return kDefaultWidth;
}

inline constexpr bool Enabled() noexcept {
	return false;
}

} // namespace electricdb