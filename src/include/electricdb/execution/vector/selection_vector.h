#pragma once

namespace electricdb {
class SelectionVector {
	public:
		explicit SelectionVector(uint32_t capacity);
		uint32_t size() const noexcept;
		uint32_t operator[](uint32_t idx) const;
		void set(uint32_t idx, uint32_t val);
		void set_size(uint32_t size);
		void reset();
	private:
		uint32_t indices_;
		uint32_t size_;

};
} // namespace electricdb
