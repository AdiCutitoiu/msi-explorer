#pragma once
#include "stdafx.h"
#include "MultipleExpression.h"

class OrExpression : public MultipleExpression
{
public:
  template <typename... Args>
  OrExpression(Args... aArgs);

protected:
  std::wstring BuildCondition() const override;
};

template <typename... Args>
inline OrExpression::OrExpression(Args... aArgs)
  : MultipleExpression(std::forward<Args &&>(aArgs)...)
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
