#include "electricdb/util/hash.h"

namespace electricdb {

uint64_t Hash::u64(uint64_t v) {
	return MurmurHash64(v);
}

uint64_t Hash::i64(int64_t v) {
	return MurmurHash64(static_cast<uint64_t>(v));
}

uint64_t Hash::u32(uint32_t v) {
	return MurmurHash64(static_cast<uint64_t>(v));
}

uint64_t Hash::i32(int32_t v) {
	return MurmurHash64(static_cast<uint64_t>(static_cast<uint32_t>(v)));
}

uint64_t Hash::bytes(const void *data, size_t len) {
	const uint8_t *p = static_cast<const uint8_t *>(data);
	uint64_t h = 0;

	for (size_t i = 0; i < len; i++) {
		h ^= static_cast<uint64_t>(p[i]) << ((i & 7) * 8);
		h = MurmurHash64(h);
	}

	return h;
}

uint64_t Hash::string(std::string_view str) {
	return bytes(str.data(), str.size());
}

uint64_t Hash::combine(uint64_t h1, uint64_t h2) {
	uint64_t x = h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
	return MurmurHash64(x);
}

} // namespace electricdb
