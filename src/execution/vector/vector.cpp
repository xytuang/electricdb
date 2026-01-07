#include "electricdb/execution/vector/vector.h"

#include <cassert>
#include <stdexcept>

namespace electricdb {
Vector::Vector(LogicalType type, uint32_t capacity, Arena &arena) {
	logical_type_ = type;
	capacity_ = capacity;
	size_ = 0;
	nulls_ = std::make_unique<NullMask>(NullMask(arena, capacity));
	switch (logical_type_) {
	case LogicalType::INT32:
		data_ = reinterpret_cast<void *>(arena.Allocate<uint32_t>(capacity));
		break;
	case LogicalType::INT64:
		data_ = reinterpret_cast<void *>(arena.Allocate<uint64_t>(capacity));
		break;
	case LogicalType::FLOAT:
		data_ = reinterpret_cast<void *>(arena.Allocate<float>(capacity));
		break;
	case LogicalType::DOUBLE:
		data_ = reinterpret_cast<void *>(arena.Allocate<double>(capacity));
		break;
	case LogicalType::BOOL:
		data_ = reinterpret_cast<void *>(arena.Allocate<bool>(capacity));
		break;
	default:
		throw std::runtime_error("Unsupported type!");
	}

	selection_ = nullptr;
	null_count_ = 0;
}

Vector::Vector(Vector &&other) noexcept
	: logical_type_(other.logical_type_), size_(other.size_), capacity_(other.capacity_),
	  data_(other.data_), null_count_(other.null_count_), nulls_(std::move(other.nulls_)),
	  selection_(other.selection_) {
	other.data_ = nullptr;
	other.null_count_ = 0;
	other.size_ = 0;
	other.selection_ = 0;
}

auto Vector::operator=(Vector &&other) noexcept -> Vector & {
	if (this != &other) {
		logical_type_ = other.logical_type_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = other.data_;
		null_count_ = other.null_count_;
		nulls_ = std::move(other.nulls_);
		selection_ = other.selection_;

		other.data_ = nullptr;
		other.size_ = 0;
		other.null_count_ = 0;
		other.selection_ = nullptr;
	}

	return *this;
}
void Vector::Slice(Vector &other, uint32_t offset, uint32_t count) {
#ifndef NDEBUG
	assert(selection_ == nullptr);
	assert(!HasNulls());
	assert(offset <= size_);
	assert(offset + count <= size_);
#endif

	const uint32_t elem_size = GetTypeSize(logical_type_);

	other.logical_type_ = logical_type_;
	other.data_ = static_cast<uint8_t *>(data_) + offset * elem_size;
	other.size_ = count;
	other.capacity_ = count;

	other.nulls_.reset();
	other.null_count_ = 0;
	other.selection_ = nullptr;
}

LogicalType Vector::Type() const noexcept {
	return logical_type_;
}

uint32_t Vector::Size() const noexcept {
	return size_;
}

uint32_t Vector::Capacity() const noexcept {
	return capacity_;
}

void Vector::SetSize(uint32_t size) {
#ifndef NDEBUG
	assert(size <= capacity_);
#endif
	size_ = size;
}

bool Vector::HasNulls() const noexcept {
	return null_count_ > 0;
}

bool Vector::IsNull(uint32_t idx) const noexcept {
#ifndef NDEBUG
	assert(idx < size_);
#endif
	return nulls_->IsNull(idx);
}

void Vector::SetNull(uint32_t idx) {
#ifndef NDEBUG
	assert(idx < size_);
#endif
	if (!nulls_->IsNull(idx)) {
		nulls_->SetNull(idx);
		null_count_++;
	}
}

void Vector::ClearNull(uint32_t idx) {
#ifndef NDEBUG
	assert(idx < size_);
#endif
	if (nulls_->IsNull(idx)) {
		nulls_->ClearNull(idx);
		null_count_--;
	}
}

bool Vector::HasSelection() const noexcept {
	return selection_ != nullptr;
}

const SelectionVector *Vector::Selection() const noexcept {
	return selection_;
}

void Vector::SetSelection(const SelectionVector *sel) {
	selection_ = sel;
}

void Vector::ClearSelection() {
	selection_ = nullptr;
}

void Vector::Reset() {
	size_ = 0;
	selection_ = nullptr;
	null_count_ = 0;
	nulls_->Reset();
}

} // namespace electricdb