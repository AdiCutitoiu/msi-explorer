#pragma once
#include "Expression.h"

class VariableExpression : public Expression
{
public:
  VariableExpression(const wstring & aName, const wstring & aValue);

  void SetValue(const wstring & aValue);

protected:
  std::wstring BuildCondition() const override;

  std::map<wstring, Expression *> BuildVariableMap() override;

private:
  wstring mName;
  wstring mValue;
};
