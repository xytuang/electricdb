#include <gtest/gtest.h>

#include "electricdb/execution/vector/vector.h"
#include "electricdb/execution/vector/selection_vector.h"
#include "electricdb/util/arena.h"

namespace electricdb {
class VectorTest : public ::testing::Test {
  protected:
	Arena arena;
};

TEST_F(VectorTest, ConstructBasic) {
	Vector vec(LogicalType::INT32, 128, arena);

	EXPECT_EQ(vec.Type(), LogicalType::INT32);
	EXPECT_EQ(vec.Size(), 0u);
	EXPECT_EQ(vec.Capacity(), 128u);
	EXPECT_FALSE(vec.HasNulls());
}

TEST_F(VectorTest, DataAccess) {
	Vector vec(LogicalType::INT32, 16, arena);
	vec.SetSize(4);

	auto data = vec.Data<int32_t>();
	data[0] = 10;
	data[1] = 20;
	data[2] = 30;
	data[3] = 40;

	const auto cdata = vec.Data<int32_t>();
	EXPECT_EQ(cdata[0], 10);
	EXPECT_EQ(cdata[3], 40);
}

TEST_F(VectorTest, NullHandling) {
	Vector vec(LogicalType::INT32, 8, arena);
	vec.SetSize(5);

	EXPECT_FALSE(vec.HasNulls());

	vec.SetNull(2);
	EXPECT_TRUE(vec.HasNulls());
	EXPECT_TRUE(vec.IsNull(2));
	EXPECT_FALSE(vec.IsNull(1));

	vec.ClearNull(2);
	EXPECT_FALSE(vec.HasNulls());
	EXPECT_FALSE(vec.IsNull(2));
}

TEST_F(VectorTest, NullIdempotence) {
	Vector vec(LogicalType::INT32, 8, arena);
	vec.SetSize(4);

	vec.SetNull(1);
	vec.SetNull(1); // should not double count
	EXPECT_TRUE(vec.HasNulls());

	vec.ClearNull(1);
	EXPECT_FALSE(vec.HasNulls());

	vec.ClearNull(1); // should not underflow
	EXPECT_FALSE(vec.HasNulls());
}

TEST_F(VectorTest, ResetClearsState) {
	Vector vec(LogicalType::INT32, 8, arena);
	vec.SetSize(4);
	vec.SetNull(2);

	vec.Reset();

	EXPECT_EQ(vec.Size(), 0u);
	EXPECT_FALSE(vec.HasNulls());
}

TEST_F(VectorTest, MoveConstructor) {
	Vector vec(LogicalType::INT32, 8, arena);
	vec.SetSize(3);
	vec.SetNull(1);

	auto data = vec.Data<int32_t>();
	data[0] = 7;
	data[1] = 8;
	data[2] = 9;

	Vector moved(std::move(vec));

	EXPECT_EQ(moved.Size(), 3u);
	EXPECT_TRUE(moved.HasNulls());
	EXPECT_EQ(moved.Data<int32_t>()[2], 9);
}

TEST_F(VectorTest, MoveAssignment) {
	Vector vec1(LogicalType::INT32, 8, arena);
	vec1.SetSize(2);
	vec1.Data<int32_t>()[0] = 1;
	vec1.Data<int32_t>()[1] = 2;

	Vector vec2(LogicalType::INT32, 8, arena);
	vec2 = std::move(vec1);

	EXPECT_EQ(vec2.Size(), 2u);
	EXPECT_EQ(vec2.Data<int32_t>()[1], 2);
}

TEST_F(VectorTest, SetSizeShrinkDoesNotInvalidateAccess) {
	Vector vec(LogicalType::INT32, 8, arena);
	vec.SetSize(6);
	vec.SetNull(5);

	vec.SetSize(2);

	// HasNulls may conservatively return true
	EXPECT_TRUE(vec.HasNulls());

	// But accessing only [0, size) must be safe
	EXPECT_FALSE(vec.IsNull(0));
	EXPECT_FALSE(vec.IsNull(1));
}

#ifndef NDEBUG
TEST_F(VectorTest, OutOfBoundsNullAccessDeath) {
	Vector vec(LogicalType::INT32, 4, arena);
	vec.SetSize(2);

	EXPECT_DEATH(vec.SetNull(3), "");
}
#endif
} // namespace electricdb