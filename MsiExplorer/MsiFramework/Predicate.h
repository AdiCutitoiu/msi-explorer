#pragma once
#include "Expression.h"
#include "VariableExpression.h"

class Predicate : public Expression
{
public:
  Predicate();

  Predicate(const shared_ptr<Expression> & aExpression);

  void SetVariable(const wstring & aVariableName, const wstring & aVariableValue);

  wstring Get() const;

protected:
  virtual std::wstring BuildCondition() const override;

  virtual std::map<wstring, Expression *> BuildVariableMap() override;

private:
  shared_ptr<Expression> mExpression;
  std::map<wstring, VariableExpression *> mVariableMap;
};
