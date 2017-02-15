#pragma once
#include "Expression.h"

class UnaryExpression : public Expression
{
public:
  UnaryExpression(std::unique_ptr<Expression> aExpression);

  std::map<wstring, Expression*> GetVariables() override;
protected:
  unique_ptr<Expression> mExpression;
};