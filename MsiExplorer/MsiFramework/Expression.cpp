#include "stdafx.h"
#include "Expression.h"

std::map<wstring, Expression *> Expression::CallBuildVariableMap(Expression * aExpression)
{
  return aExpression->BuildVariableMap();
}

std::wstring Expression::CallBuildCondition(const Expression * aExpression)
{
  return aExpression->BuildCondition();
}
