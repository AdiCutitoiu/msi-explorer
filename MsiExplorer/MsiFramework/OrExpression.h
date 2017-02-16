#pragma once
#include "MultipleExpression.h"

class OrExpression : public MultipleExpression
{
public:
  OrExpression(vector<shared_ptr<Expression>> aExpressions);

  std::wstring Get() const override;
};