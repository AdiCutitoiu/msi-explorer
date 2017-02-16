#pragma once
#include "MultipleExpression.h"

class AndExpression : public MultipleExpression
{
public:
  AndExpression(vector<shared_ptr<Expression>> aExpressions);

  std::wstring Get() const override;
};
