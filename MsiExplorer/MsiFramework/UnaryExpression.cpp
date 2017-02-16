#include "stdafx.h"
#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(std::shared_ptr<Expression> aExpression)
  : mExpression(aExpression)
{
}

/*virtual*/ std::map<wstring, Expression *> UnaryExpression::BuildVariableMap()
{
  return Expression::CallBuildVariableMap(mExpression.get());
}
