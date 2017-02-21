#include "stdafx.h"
#include "VariableExpression.h"

VariableExpression::VariableExpression(const wstring & aName,
                                       const wstring & aValue,
                                       bool            aUseEqual /*= true*/)
  : mName(aName)
  , mValue(aValue)
  , mUseEqual(aUseEqual)
{
}

/*virtual*/ std::wstring VariableExpression::BuildCondition() const
{
  return L"`" + mName + L"`" + (mUseEqual ? L"=" : L"<>") + L'\'' + mValue + L'\'';
}

/*virtual*/ std::map<wstring, Expression *> VariableExpression::BuildVariableMap()
{
  return { { mName, this } };
}

void VariableExpression::SetValue(const wstring & aValue)
{
  mValue = aValue;
}
