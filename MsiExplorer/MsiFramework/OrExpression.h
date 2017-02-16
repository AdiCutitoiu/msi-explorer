#pragma once
#include "MultipleExpression.h"

class OrExpression : public MultipleExpression
{
public:
  OrExpression(vector<shared_ptr<Expression>> aExpressions);

protected:
  std::wstring BuildCondition() const override;
};
