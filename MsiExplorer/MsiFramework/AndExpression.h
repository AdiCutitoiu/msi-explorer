#pragma once
#include "stdafx.h"
#include "MultipleExpression.h"

class AndExpression : public MultipleExpression
{
public:
  template <typename... Args>
  AndExpression(Args... aArgs);

protected:
  std::wstring BuildCondition() const override;
};

template <typename... Args>
inline AndExpression::AndExpression(Args... aArgs)
  : MultipleExpression(std::forward<Args &&>(aArgs)...)
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
