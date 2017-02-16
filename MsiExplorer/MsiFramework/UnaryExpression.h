#pragma once
#include "Expression.h"

class UnaryExpression : public Expression
{
public:
  UnaryExpression(std::shared_ptr<Expression> aExpression);

  std::map<wstring, Expression*> GetVariables() override;
protected:
  shared_ptr<Expression> mExpression;
};