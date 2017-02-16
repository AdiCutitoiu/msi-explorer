#include "stdafx.h"
#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(std::shared_ptr<Expression> aExpression)
  : mExpression(aExpression)
{
}

std::map<wstring, Expression *> UnaryExpression::GetVariables()
{
  return mExpression->GetVariables();
}
