#pragma once
#include "Expression.h"

class MultipleExpression : public Expression
{
public:
  MultipleExpression(vector<shared_ptr<Expression>> aExpressions);

protected:
  std::map<wstring, Expression *> BuildVariableMap() override;

  vector<shared_ptr<Expression>> mExpressions;
};
