#pragma once

#include <cstdint>
#include <type_traits>

namespace electricdb {
enum class LogicalType : uint8_t { INT32, INT64, FLOAT, DOUBLE, STRING, BOOL };

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
}
