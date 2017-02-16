#pragma once
#include "UnaryExpression.h"

class NotExpression : public UnaryExpression
{
public:
  NotExpression(std::shared_ptr<Expression> aExpression);

  std::wstring Get() const override;
};
