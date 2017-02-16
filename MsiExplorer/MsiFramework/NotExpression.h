#pragma once
#include "UnaryExpression.h"

// TO DO: remove this class
class NotExpression : public UnaryExpression
{
public:
  explicit NotExpression(std::shared_ptr<Expression> aExpression);

protected:
  std::wstring BuildCondition() const override;
};
