#include <gtest/gtest.h>
#include "electricdb/execution/expressions/leaf_expression.h"
#include "electricdb/execution/expressions/unary_expression.h"
#include "electricdb/util/arena.h"
#include "electricdb/execution/context/execution_context.h"

namespace electricdb {
TEST(UnaryExpressionTest, BasicNot) {
    ExecutionContext ctx;
    Arena &arena = ctx.Arena();

    std::vector<Vector> input;
    input.emplace_back(LogicalType::BOOL, 4, arena);
    input[0].SetSize(4);

    auto in = input[0].Data<bool>();
    in[0] = true;
    in[1] = false;
    in[2] = true;
    in[3] = false;

    ctx.SetInput(&input);

    ColumnExpr col(0, LogicalType::BOOL);
    NotExpr not_expr(&col);

    Vector &result = ctx.GetTempVector(LogicalType::BOOL);
    result.SetSize(4);

    not_expr.Execute(ctx, result);

    auto out = result.Data<bool>();
    EXPECT_FALSE(out[0]);
    EXPECT_TRUE(out[1]);
    EXPECT_FALSE(out[2]);
    EXPECT_TRUE(out[3]);
}

TEST(UnaryExpressionTest, NotExprPropagatesNulls) {
    ExecutionContext ctx;
    Arena &arena = ctx.Arena();

    std::vector<Vector> input;
    input.emplace_back(LogicalType::BOOL, 3, arena);
    input[0].SetSize(3);

    auto in = input[0].Data<bool>();
    in[0] = true;
    in[1] = false;
    in[2] = true;
    input[0].SetNull(1);

    ctx.SetInput(&input);

    ColumnExpr col(0, LogicalType::BOOL);
    NotExpr not_expr(&col);

    Vector &result = ctx.GetTempVector(LogicalType::BOOL);
    result.SetSize(3);

    not_expr.Execute(ctx, result);

    ASSERT_TRUE(result.IsNull(1));
    ASSERT_FALSE(result.Data<bool>()[0]);
    ASSERT_FALSE(result.Data<bool>()[2]);
}

TEST(UnaryExpressionTest, NegateExprNegatesInt32) {
    ExecutionContext ctx;
    Arena &arena = ctx.Arena();

    std::vector<Vector> input;
    input.emplace_back(LogicalType::INT32, 3, arena);
    input[0].SetSize(3);

    auto in = input[0].Data<int32_t>();
    in[0] = 10;
    in[1] = -5;
    in[2] = 0;

    ctx.SetInput(&input);

    ColumnExpr col(0, LogicalType::INT32);
    NegateExpr neg(&col);

    Vector result(LogicalType::INT32, 3, arena);
    result.SetSize(3);

    neg.Execute(ctx, result);

    auto out = result.Data<int32_t>();
    EXPECT_EQ(out[0], -10);
    EXPECT_EQ(out[1], 5);
    EXPECT_EQ(out[2], 0);
}
} // namespace electricdb