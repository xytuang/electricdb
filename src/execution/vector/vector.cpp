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
		data_ = reinterpret_cast<void *>(arena.allocate<uint32_t>(capacity));
		break;
	case LogicalType::INT64:
		data_ = reinterpret_cast<void *>(arena.allocate<uint64_t>(capacity));
		break;
	case LogicalType::FLOAT:
		data_ = reinterpret_cast<void *>(arena.allocate<float>(capacity));
		break;
	case LogicalType::DOUBLE:
		data_ = reinterpret_cast<void *>(arena.allocate<double>(capacity));
		break;
	case LogicalType::BOOL:
		data_ = reinterpret_cast<void *>(arena.allocate<bool>(capacity));
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
	assert(size <= capacity_);
	size_ = size;
}

bool Vector::HasNulls() const noexcept {
	return null_count_ > 0;
}

bool Vector::IsNull(uint32_t idx) const noexcept {
	assert(idx < size_);
	return nulls_->IsNull(idx);
}

void Vector::SetNull(uint32_t idx) {
	assert(idx < size_);
	if (!nulls_->IsNull(idx)) {
		nulls_->SetNull(idx);
		null_count_++;
	}
}

void Vector::ClearNull(uint32_t idx) {
	assert(idx < size_);
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