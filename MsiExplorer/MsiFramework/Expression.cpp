#include "stdafx.h"
#include "Expression.h"

std::map<wstring, Expression *> Expression::GetVariables(Expression * aExpression)
{
  return aExpression->GetVariables();
}
