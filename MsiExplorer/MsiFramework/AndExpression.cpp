#include "stdafx.h"
#include "AndExpression.h"

AndExpression::AndExpression(vector<shared_ptr<Expression>> aExpressions)
  : MultipleExpression(aExpressions)
{
}

/*virtual*/ std::wstring AndExpression::BuildCondition() const
{
  return accumulate(
    mExpressions.begin(),
    mExpressions.end(),
    wstring(),
    [](const wstring & aConditionStr, const shared_ptr<Expression> & aExpression) {

      auto currentExp = L'(' + Expression::CallBuildCondition(aExpression.get()) + L')';

      return aConditionStr.empty() ? currentExp : aConditionStr + L" AND " + currentExp;
    });
}
