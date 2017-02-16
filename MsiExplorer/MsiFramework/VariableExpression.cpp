#include "stdafx.h"
#include "VariableExpression.h"

VariableExpression::VariableExpression(const wstring & aName, const wstring & aValue)
  : mName(aName)
  , mValue(aValue)
{
}

std::wstring VariableExpression::Get() const
{
  return L"(`" + mName + L"'=" + mValue + L')';
}

std::map<wstring, Expression *> VariableExpression::GetVariables()
{
  return { { mName, this } };
}

void VariableExpression::SetValue(const wstring & aValue)
{
  mValue = aValue;
}
