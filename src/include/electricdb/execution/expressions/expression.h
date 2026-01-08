#pragma once

#include "electricdb/common/types.h"
#include "electricdb/execution/context/execution_context.h"
#include "electricdb/execution/vector/vector.h"

namespace electricdb {

/**
 * @brief Abstract Expression class. All other expression classes are child classes of this class
 *
 */
class Expression {
  public:
	/** @brief Executes this expression */
	virtual void Execute(ExecutionContext &ctx, Vector &result) = 0;
	/** @brief Default destructor for all expressions */
	virtual ~Expression() = default;
	/** @brief Get type returned by expression */
	virtual LogicalType Type() const = 0;
};

} // namespace electricdb