#include "electricdb/execution/vector/selection_vector.h"

namespace electricdb {

SelectionVector::SelectionVector() noexcept {
    data_ = nullptr;
    capacity_ = 0;
}

SelectionVector::SelectionVector(Arena &arena, idx_t capacity) {
    data_ = reinterpret_cast<sel_t *>(arena.allocate<sel_t>(capacity));
    capacity_ = capacity;
}

void SelectionVector::Reset() noexcept {
    data_ = nullptr;
}

void SelectionVector::Reference(const SelectionVector &other) noexcept {
    data_ = other.data_;
    capacity_ = other.capacity_;
}

idx_t SelectionVector::Invert(
    const SelectionVector &src,
    SelectionVector &dst,
    idx_t input_count,
    idx_t src_count) {
        idx_t src_idx = 0;
        idx_t dst_idx = 0;

        for (idx_t i = 0; i < input_count; i++) {
            if (src_idx < src_count && src.Get(src_idx) == i) {
                src_idx++;
                continue;
            }
            dst.Set(dst_idx++, i);
        }
        
        return dst_idx;
    }
} // namespace electricdb