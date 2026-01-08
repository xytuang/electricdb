#include <gtest/gtest.h>
#include "electricdb/execution/expressions/leaf_expression.h"
#include "electricdb/execution/expressions/binary_expression.h"
#include "electricdb/util/arena.h"
#include "electricdb/execution/context/execution_context.h"

namespace electricdb {
TEST(BinaryExpressionTest, SimpleAdd) {
    ExecutionContext ctx;
    Arena &arena = ctx.GetArena();

    std::vector<Vector> input;
    input.emplace_back(LogicalType::INT32, 3, arena);
    input.emplace_back(LogicalType::INT32, 3, arena);

    input[0].SetSize(3);
    input[1].SetSize(3);

    input[0].Data<int32_t>()[0] = 1;
    input[0].Data<int32_t>()[1] = 2;
    input[0].Data<int32_t>()[2] = 3;

    input[1].Data<int32_t>()[0] = 10;
    input[1].Data<int32_t>()[1] = 20;
    input[1].Data<int32_t>()[2] = 30;

    ctx.SetInput(&input);

    ColumnExpr left(0, LogicalType::INT32);
    ColumnExpr right(1, LogicalType::INT32);
    AddExpr add(&left, &right);

    Vector &result = ctx.GetTempVector(LogicalType::INT32);
    result.SetSize(3);

    add.Execute(ctx, result);

    auto out = result.Data<int32_t>();
    EXPECT_EQ(out[0], 11);
    EXPECT_EQ(out[1], 22);
    EXPECT_EQ(out[2], 33);
}


TEST(BinaryExpressionTest, AddExprNullPropagation) {
    ExecutionContext ctx;
    Arena &arena = ctx.GetArena();

    std::vector<Vector> input;
    input.emplace_back(LogicalType::INT32, 2, arena);
    input.emplace_back(LogicalType::INT32, 2, arena);

    input[0].SetSize(2);
    input[1].SetSize(2);

    input[0].Data<int32_t>()[0] = 1;
    input[0].Data<int32_t>()[1] = 2;
    input[1].Data<int32_t>()[0] = 10;
    input[1].Data<int32_t>()[1] = 20;

    input[0].SetNull(1);

    ctx.SetInput(&input);

    ColumnExpr left(0, LogicalType::INT32);
    ColumnExpr right(1, LogicalType::INT32);
    AddExpr add(&left, &right);

    Vector &result = ctx.GetTempVector(LogicalType::INT32);
    result.SetSize(2);

    add.Execute(ctx, result);

    ASSERT_FALSE(result.IsNull(0));
    ASSERT_TRUE(result.IsNull(1));
}
} // namespace electricdb