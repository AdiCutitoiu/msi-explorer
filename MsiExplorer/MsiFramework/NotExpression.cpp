#include "stdafx.h"
#include "NotExpression.h"

NotExpression::NotExpression(std::shared_ptr<Expression> aExpression)
  : UnaryExpression(aExpression)
{
}

std::wstring NotExpression::Get() const
{
  return L"NOT " + mExpression->Get();
}
