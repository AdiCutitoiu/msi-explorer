#include "stdafx.h"
#include "OrExpression.h"

OrExpression::OrExpression(vector<shared_ptr<Expression>> aExpressions)
  : MultipleExpression(aExpressions)
{
}

std::wstring OrExpression::Get() const
{
  return accumulate(mExpressions.begin(),
                    mExpressions.end(),
                    wstring(),
                    [](const wstring & aConditionStr, const shared_ptr<Expression> & aExpression) {

                      auto currentExp = L'(' + aExpression->Get() + L')';

                      return aConditionStr.empty() ? currentExp
                                                   : aConditionStr + L" OR " + currentExp;
                    });
}
