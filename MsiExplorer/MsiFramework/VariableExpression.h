#pragma once
#include "Expression.h"

class VariableExpression : public Expression
{
public:
  /**
   * @param aName the name of the variable
   *
   * @param aValue to be compared with the variable
   *
   * @param aIsEqual if true, the operator "=" is used, else "<>" is used
   */
  VariableExpression(const wstring & aName, const wstring & aValue, bool aUseEqual = true);

  void SetValue(const wstring & aValue);

protected:
  std::wstring BuildCondition() const override;

  std::map<wstring, Expression *> BuildVariableMap() override;

private:
  wstring mName;
  wstring mValue;
  bool    mUseEqual;
};
