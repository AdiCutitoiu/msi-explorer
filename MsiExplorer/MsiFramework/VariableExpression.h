#pragma once
#include "Expression.h"

class VariableExpression : public Expression
{
public:
  VariableExpression(const wstring & aName, const wstring & aValue);

  std::wstring Get() const override;

  std::map<wstring, Expression*> GetVariables() override;

  void SetValue(const wstring & aValue);

private:
  wstring mName;
  wstring mValue;
};