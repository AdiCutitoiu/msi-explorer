#include "stdafx.h"
#include "VariableExpression.h"

VariableExpression::VariableExpression(const wstring & aName, const wstring & aValue)
  : mName(aName)
  , mValue(aValue)
{
}

/*virtual*/ std::wstring VariableExpression::BuildCondition() const
{
  return L"`" + mName + L"`=" + mValue;
}

/*virtual*/ std::map<wstring, Expression *> VariableExpression::BuildVariableMap()
{
  return { { mName, this } };
}

void VariableExpression::SetValue(const wstring & aValue)
{
  mValue = aValue;
}
