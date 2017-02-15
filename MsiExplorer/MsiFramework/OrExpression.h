#pragma once
#include "MultipleExpression.h"

class OrExpression : public MultipleExpression
{
public:
  OrExpression(vector<unique_ptr<Expression>> aExpressions);

  std::wstring Get() const override;
};