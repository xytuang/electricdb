#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace electricdb {

/**
 * @brief Stateless hash helper functions
 *
 */
class Hash {
  public:
	/**
	 * @brief Hash raw bytes
	 *
	 * @param data Bytes to hash
	 * @param len Number of bytes to hash
	 * @return uint64_t A lookup key
	 */
	static uint64_t bytes(const void *data, size_t len);

	/**
	 * @brief Hash string bytes (no null terminator)
	 *
	 * @param data String to hash
	 * @return uint64_t A lookup key
	 */
	static uint64_t string(std::string_view str);

	/** Hash primitives */
	static uint64_t u64(uint64_t v);
	static uint64_t i64(int64_t v);
	static uint64_t u32(uint32_t v);
	static uint64_t i32(int32_t v);

	/** Combine two hash values */
	static uint64_t combine(uint64_t h1, uint64_t h2);

  private:
	/**
	 * @brief Taken straight from DuckDB
	 * See https://github.com/duckdb/duckdb/blob/main/src/include/duckdb/common/types/hash.hpp#L36
	 *
	 * @param x Value we are trying to hash
	 * @return uint64_t
	 */
	static inline uint64_t MurmurHash64(uint64_t x) {
		x ^= x >> 32;
		x *= 0xd6e8feb86659fd93U;
		x ^= x >> 32;
		x *= 0xd6e8feb86659fd93U;
		x ^= x >> 32;
		return x;
	}
};
} // namespace electricdb