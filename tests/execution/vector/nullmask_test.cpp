#include <gtest/gtest.h>
#include "electricdb/execution/vector/nullmask.h"

namespace electricdb {

class NullMaskTest : public testing::Test {
    protected:
        Arena arena;
};

TEST_F(NullMaskTest, IsNullTest) {
    /** Create nullmask for 128 elements */
    NullMask nullmask = NullMask(arena, 128);

    for (uint32_t i = 0; i < 128; i++) {
        EXPECT_EQ(nullmask.IsNull(i), false);
    }
}

TEST_F(NullMaskTest, SetNullTest) {
    /** Create nullmask for 128 elements */
    NullMask nullmask = NullMask(arena, 128);

    for (uint32_t i = 0; i < 128; i++) {
        EXPECT_EQ(nullmask.IsNull(i), false);
        nullmask.SetNull(i);
        EXPECT_EQ(nullmask.IsNull(i), true);
    }
}

TEST_F(NullMaskTest, ClearNullTest) {
    /** Create nullmask for 128 elements */
    NullMask nullmask = NullMask(arena, 128);

    for (uint32_t i = 0; i < 128; i++) {
        EXPECT_EQ(nullmask.IsNull(i), false);
        nullmask.SetNull(i);
        EXPECT_EQ(nullmask.IsNull(i), true);
        nullmask.ClearNull(i);
        EXPECT_EQ(nullmask.IsNull(i), false);
    }
}

TEST_F(NullMaskTest, ResetTest) {
    /** Create nullmask for 128 elements */
    NullMask nullmask = NullMask(arena, 128);

    for (uint32_t i = 0; i < 128; i++) {
        EXPECT_EQ(nullmask.IsNull(i), false);
        nullmask.SetNull(i);
        EXPECT_EQ(nullmask.IsNull(i), true);
    }

    nullmask.Reset();

    for (uint32_t i = 0; i < 128; i++) {
        EXPECT_EQ(nullmask.IsNull(i), false);
    }
}

} // namespace electricdb