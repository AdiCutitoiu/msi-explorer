#include "stdafx.h"
#include "AndExpression.h"

AndExpression::AndExpression(vector<shared_ptr<Expression>> aExpressions)
  : MultipleExpression(aExpressions)
{
}

std::wstring AndExpression::Get() const
{
  return accumulate(mExpressions.begin(),
                    mExpressions.end(),
                    wstring(),
                    [](const wstring & aConditionStr, const shared_ptr<Expression> & aExpression) {

                      auto currentExp = L'(' + aExpression->Get() + L')';

                      return aConditionStr.empty() ? currentExp
                                                   : aConditionStr + L" AND " + currentExp;
                    });
}
