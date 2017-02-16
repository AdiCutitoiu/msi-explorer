#pragma once
#include "MultipleExpression.h"

class OrExpression : public MultipleExpression
{
public:
  explicit OrExpression(vector<shared_ptr<Expression>> aExpressions);

protected:
  std::wstring BuildCondition() const override;
};
