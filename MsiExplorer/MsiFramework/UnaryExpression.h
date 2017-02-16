#pragma once
#include "Expression.h"

class UnaryExpression : public Expression
{
public:
  UnaryExpression(std::shared_ptr<Expression> aExpression);

protected:
  std::map<wstring, Expression *> BuildVariableMap() override;

  shared_ptr<Expression> mExpression;
};
