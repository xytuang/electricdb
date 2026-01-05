#include <gtest/gtest.h>
#include "electricdb/util/arena.h"

namespace electricdb {
class ArenaTest : public testing::Test {
    protected:
        Arena arena;
};

TEST_F(ArenaTest, AllocateTest) {
    size_t num_ints = (1 << 20) / sizeof(int);

    int *int_arr1 = reinterpret_cast<int *>(arena.allocate(sizeof(int) * (num_ints - 1), alignof(int)));
    int *int_arr2 = reinterpret_cast<int *>(arena.allocate(sizeof(int) * 2, alignof(int)));

    int_arr1[0] = 1;
    int_arr2[0] = 2;
    
    EXPECT_GE(arena.bytes_used(), (num_ints + 1) * sizeof(int));
    EXPECT_GE(arena.bytes_reserved(), 1 << 21);
}
} // namespace electricdb