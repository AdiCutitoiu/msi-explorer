#pragma once
#include "UnaryExpression.h"

class NotExpression : public UnaryExpression
{
public:
  NotExpression(std::unique_ptr<Expression> aExpression);

  std::wstring Get() const override;

};