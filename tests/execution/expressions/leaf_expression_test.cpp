#include <gtest/gtest.h>
#include "electricdb/execution/expressions/leaf_expression.h"
#include "electricdb/util/arena.h"
#include "electricdb/execution/context/execution_context.h"

namespace electricdb {
TEST(LeafExpressionTest, ColumnExprSimpleReference) {
    ExecutionContext ctx;

    Arena &arena = ctx.GetArena();

    std::vector<Vector> input;
    input.emplace_back(LogicalType::INT32, 4, arena);

    auto &col = input[0];
    col.SetSize(4);

    auto data = col.Data<int32_t>();
    data[0] = 10;
    data[1] = 20;
    data[2] = 30;
    data[3] = 40;

    ctx.SetInput(&input);

    ColumnExpr expr(/*column_idx=*/0, LogicalType::INT32);

    Vector &result = ctx.GetTempVector(LogicalType::INT32);
    result.SetSize(4);

    expr.Execute(ctx, result);

    // zero-copy reference
    ASSERT_EQ(result.Data<int32_t>(), col.Data<int32_t>());
    ASSERT_EQ(result.Size(), 4);
    ASSERT_EQ(result.Type(), LogicalType::INT32);
}

TEST(LeafExpressionTest, ColumnExprPreservesSelection) {
    ExecutionContext ctx;
    Arena &arena = ctx.GetArena();

    std::vector<Vector> input;
    input.emplace_back(LogicalType::INT32, 4, arena);
    input[0].SetSize(4);

    SelectionVector sel(arena, 2);
    sel.Set(0, 1);
    sel.Set(1, 3);

    ctx.SetInput(&input);
    ctx.SetSelection(&sel);

    ColumnExpr expr(0, LogicalType::INT32);

    Vector &result = ctx.GetTempVector(LogicalType::INT32);
    result.SetSize(2);

    expr.Execute(ctx, result);
}

TEST(LeafExpressionTest, ConstantExprFillConstant) {
    ExecutionContext ctx;

    Value v;
    v.SetType(LogicalType::INT32);
    int32_t num = 7;
    v.Set(num);

    ConstantExpr expr(v);

    Vector &result = ctx.GetTempVector(LogicalType::INT32);
    result.SetSize(4);

    expr.Execute(ctx, result);

    auto out = result.Data<int32_t>();
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(out[i], 7);
    }
}

TEST(LeafExpressionTest, ConstantExprRespectsSelection) {
    ExecutionContext ctx;
    Arena &arena = ctx.GetArena();

    SelectionVector sel(arena, 2);
    sel.Set(0, 0);
    sel.Set(1, 2);

    ctx.SetSelection(&sel);

    Value v;
    v.SetType(LogicalType::INT32);
    int32_t num = 5;
    v.Set(num);

    ConstantExpr expr(v);

    Vector &result = ctx.GetTempVector(LogicalType::INT32);
    result.SetSize(3);

    expr.Execute(ctx, result);

    auto out = result.Data<int32_t>();
    ASSERT_EQ(out[0], 5);
    ASSERT_EQ(out[2], 5);
}
} // namespace electricdb