#pragma once
#include "Expression.h"

class MultipleExpression : public Expression
{
public:
  MultipleExpression(vector<unique_ptr<Expression>> aExpressions);

  std::map<wstring, Expression*> GetVariables() override;

protected:
  vector<unique_ptr<Expression>> mExpressions;
};