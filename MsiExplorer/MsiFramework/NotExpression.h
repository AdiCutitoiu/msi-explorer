#pragma once
#include "UnaryExpression.h"

class NotExpression : public UnaryExpression
{
public:
  NotExpression(std::shared_ptr<Expression> aExpression);

protected:
  std::wstring BuildCondition() const override;
};
