#include <gtest/gtest.h>
#include "electricdb/execution/vector/selection_vector.h"

namespace electricdb {
class SelectionVectorTest : public testing::Test {
    protected:
        Arena arena;
};

TEST_F(SelectionVectorTest, ConstructorTest) {
    SelectionVector identity;
    SelectionVector with_mapping(arena, 128);

    EXPECT_EQ(identity.Data(), nullptr);
    EXPECT_NE(with_mapping.Data(), nullptr);
}

TEST_F(SelectionVectorTest, IdentityGet) {
    SelectionVector sel;

    for (idx_t i = 0; i < 100; i++) {
        EXPECT_EQ(sel.Get(i), i);
    }

    EXPECT_FALSE(sel.IsSet());
}

TEST_F(SelectionVectorTest, SetAndGet) {
    SelectionVector sel(arena, 16);

    sel.Set(0, 5);
    sel.Set(1, 7);
    sel.Set(2, 9);

    EXPECT_TRUE(sel.IsSet());
    EXPECT_EQ(sel.Get(0), 5);
    EXPECT_EQ(sel.Get(1), 7);
    EXPECT_EQ(sel.Get(2), 9);
}

TEST_F(SelectionVectorTest, GetUnsafe) {
    SelectionVector sel(arena, 8);

    for (idx_t i = 0; i < 8; i++) {
        sel.Set(i, i * 2);
    }

    for (idx_t i = 0; i < 8; i++) {
        EXPECT_EQ(sel.GetUnsafe(i), i * 2);
    }
}

TEST_F(SelectionVectorTest, ResetRestoresIdentity) {
    SelectionVector sel(arena, 8);

    sel.Set(0, 3);
    sel.Set(1, 4);

    EXPECT_TRUE(sel.IsSet());

    sel.Reset();

    EXPECT_FALSE(sel.IsSet());
    EXPECT_EQ(sel.Get(0), 0);
    EXPECT_EQ(sel.Get(1), 1);
}

TEST_F(SelectionVectorTest, ReferenceSharesMapping) {
    SelectionVector src(arena, 8);
    src.Set(0, 2);
    src.Set(1, 4);

    SelectionVector ref;
    ref.Reference(src);

    EXPECT_TRUE(ref.IsSet());
    EXPECT_EQ(ref.Get(0), 2);
    EXPECT_EQ(ref.Get(1), 4);
}

TEST_F(SelectionVectorTest, SwapEntries) {
    SelectionVector sel(arena, 4);

    sel.Set(0, 10);
    sel.Set(1, 20);

    sel.Swap(0, 1);

    EXPECT_EQ(sel.GetUnsafe(0), 20);
    EXPECT_EQ(sel.GetUnsafe(1), 10);
}

TEST_F(SelectionVectorTest, InvertBasic) {
    SelectionVector src(arena, 8);
    src.Set(0, 1);
    src.Set(1, 3);
    src.Set(2, 5);

    SelectionVector dst(arena, 8);

    idx_t out_count = SelectionVector::Invert(src, dst, 7, 3);

    EXPECT_EQ(out_count, 4);
    EXPECT_EQ(dst.GetUnsafe(0), 0);
    EXPECT_EQ(dst.GetUnsafe(1), 2);
    EXPECT_EQ(dst.GetUnsafe(2), 4);
    EXPECT_EQ(dst.GetUnsafe(3), 6);
}

TEST_F(SelectionVectorTest, InvertEmptySource) {
    SelectionVector src;
    SelectionVector dst(arena, 8);

    idx_t out_count = SelectionVector::Invert(src, dst, 5, 0);

    EXPECT_EQ(out_count, 5);
    for (idx_t i = 0; i < 5; i++) {
        EXPECT_EQ(dst.GetUnsafe(i), i);
    }
}

TEST_F(SelectionVectorTest, InvertFullSource) {
    SelectionVector src(arena, 4);
    for (idx_t i = 0; i < 4; i++) {
        src.Set(i, i);
    }

    SelectionVector dst(arena, 4);

    idx_t out_count = SelectionVector::Invert(src, dst, 4, 4);

    EXPECT_EQ(out_count, 0);
}
}