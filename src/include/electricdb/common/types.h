#pragma once

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace electricdb {
enum class LogicalType : uint8_t { INT32, INT64, FLOAT, DOUBLE, STRING, BOOL, INVALID };

template <typename T>
struct LogicalTypeTrait;

template <>
struct LogicalTypeTrait<int32_t> {
	static constexpr LogicalType type = LogicalType::INT32;
};

template <>
struct LogicalTypeTrait<int64_t> {
	static constexpr LogicalType type = LogicalType::INT64;
};

template <>
struct LogicalTypeTrait<float> {
	static constexpr LogicalType type = LogicalType::FLOAT;
};

template <>
struct LogicalTypeTrait<double> {
	static constexpr LogicalType type = LogicalType::DOUBLE;
};

template <>
struct LogicalTypeTrait<bool> {
	static constexpr LogicalType type = LogicalType::BOOL;
};

template <typename T>
bool TypeMatches(LogicalType type) {
	return LogicalTypeTrait<std::remove_cv_t<T>>::type == type;
}

inline uint32_t GetTypeSize(LogicalType type) {
	switch (type) {
	case LogicalType::INT32:
		return sizeof(int32_t);
	case LogicalType::INT64:
		return sizeof(int64_t);
	case LogicalType::FLOAT:
		return sizeof(float);
	case LogicalType::DOUBLE:
		return sizeof(double);
	case LogicalType::BOOL:
		return sizeof(bool);
	default:
		throw std::runtime_error("Unsupported type!");
	}
}

/**
 * @brief This is used to represent constants
 *
 */
class Value {
  public:
	Value() : type_(LogicalType::INVALID), is_null_(true) {}
	/** @brief Get the type of this value */
	LogicalType Type() const { return type_; }
	/** Check if this value is null */
	bool IsNull() const { return is_null_; }

	template <typename T>
	T Get() const {
#ifndef NDEBUG
		assert(!is_null_);
		assert(TypeMatches<T>(type_));
#endif
		if constexpr (std::is_same_v<T, int32_t>) {
			return i32;
		} else if constexpr (std::is_same_v<T, int64_t>) {
			return i64;
		} else if constexpr (std::is_same_v<T, float>) {
			return f32;
		} else if constexpr (std::is_same_v<T, double>) {
			return f64;
		} else if constexpr (std::is_same_v<T, bool>) {
			return boolean;
		} else {
			static_assert(sizeof(T) == 0, "Unsupported Value::Get type");
		}
	}

	void SetNull() { is_null_ = true; }

	template <typename T>
	void Set(T val) {
		if constexpr (std::is_same_v<T, int32_t>) {
			i32 = val;
		} else if constexpr (std::is_same_v<T, int64_t>) {
			i64 = val;
		} else if constexpr (std::is_same_v<T, float>) {
			f32 = val;
		} else if constexpr (std::is_same_v<T, double>) {
			f64 = val;
		} else if constexpr (std::is_same_v<T, bool>) {
			boolean = val;
		} else {
			static_assert(sizeof(T) == 0, "Unsupported Value::Get type");
		}
		is_null_ = false;
	}

	LogicalType GetType() const { return type_; }

	void SetType(LogicalType type) {
		type_ = type;
		is_null_ = true;
	}

  private:
	LogicalType type_;
	bool is_null_;
	union {
		int32_t i32;
		int64_t i64;
		float f32;
		double f64;
		bool boolean;
	};
};
} // namespace electricdb
