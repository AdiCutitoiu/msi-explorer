#include "stdafx.h"
#include "OrExpression.h"

OrExpression::OrExpression(vector<shared_ptr<Expression>> aExpressions)
  : MultipleExpression(aExpressions)
{
}

/*virtual*/ std::wstring OrExpression::BuildCondition() const
{
  return accumulate(
    mExpressions.begin(),
    mExpressions.end(),
    wstring(),
    [this](const wstring & aConditionStr, const shared_ptr<Expression> & aExpression) {

      auto currentExp = L'(' + Expression::CallBuildCondition(aExpression.get()) + L')';

      return aConditionStr.empty() ? currentExp : aConditionStr + L" OR " + currentExp;
    });
}
