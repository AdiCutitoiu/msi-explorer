#pragma once
#include "Expression.h"

class MultipleExpression : public Expression
{
public:
  MultipleExpression(vector<shared_ptr<Expression>> aExpressions);

  std::map<wstring, Expression*> GetVariables() override;

protected:
  vector<shared_ptr<Expression>> mExpressions;
};