#pragma once

#include <cstddef>
#include <cstdint>

namespace electricdb {

class Simd {
  public:
	// SIMD width in bytes (e.g., 16 for SSE, 32 for AVX2)
	static size_t width();

	// Load/store
	static void load(const void *src, void *dst);
	static void store(const void *src, void *dst);

	// Comparisons
	// Returns a bitmask of lanes where comparison is true
	static uint32_t cmp_eq_i32(const int32_t *a, const int32_t *b);
	static uint32_t cmp_lt_i32(const int32_t *a, const int32_t *b);
	static uint32_t cmp_gt_i32(const int32_t *a, const int32_t *b);

	// Mask utilities
	static uint32_t mask_all();
	static uint32_t mask_none();
	static size_t popcount(uint32_t mask);

	// Prefetch hint
	static void prefetch(const void *ptr);

  private:
	Simd() = delete;
};

} // namespace electricdb
