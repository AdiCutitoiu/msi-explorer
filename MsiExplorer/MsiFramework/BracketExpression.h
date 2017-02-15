#pragma once
#include "UnaryExpression.h"

class BracketExpression : public UnaryExpression
{
public:
  BracketExpression(std::unique_ptr<Expression> aExpression);

  std::wstring Get() const override;
};