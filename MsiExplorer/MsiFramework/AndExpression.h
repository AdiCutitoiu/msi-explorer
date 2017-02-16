#pragma once
#include "MultipleExpression.h"

class AndExpression : public MultipleExpression
{
public:
  AndExpression(vector<shared_ptr<Expression>> aExpressions);

protected:
  std::wstring BuildCondition() const override;
};
