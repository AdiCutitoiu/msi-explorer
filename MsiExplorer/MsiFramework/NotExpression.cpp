#include "stdafx.h"
#include "NotExpression.h"

NotExpression::NotExpression(std::shared_ptr<Expression> aExpression)
  : UnaryExpression(aExpression)
{
}

/*virtual*/ std::wstring NotExpression::BuildCondition() const
{
  return L"NOT (" + Expression::CallBuildCondition(mExpression.get()) + L")";
}
