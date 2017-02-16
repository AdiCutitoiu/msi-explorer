#include "stdafx.h"
#include "MultipleExpression.h"

MultipleExpression::MultipleExpression(vector<shared_ptr<Expression>> aExpressions)
  : mExpressions(move(aExpressions))
{
  assert(mExpressions.size() >= 2);
}

/*virtual*/ std::map<wstring, Expression *> MultipleExpression::BuildVariableMap()
{
  // build a map containing all the variables used in this expression
  return accumulate(
    mExpressions.begin(),
    mExpressions.end(),
    map<wstring, Expression *>(),
    [this](const map<wstring, Expression *> & aPrevResult, shared_ptr<Expression> & aExpression) {
      map<wstring, Expression *> variableUnion;

      // get current variables
      auto currentVariables = Expression::CallBuildVariableMap(aExpression.get());

      // add current variables to the union of variables
      set_union(aPrevResult.begin(),
                aPrevResult.end(),
                currentVariables.begin(),
                currentVariables.end(),
                inserter(variableUnion, variableUnion.begin()));

      // return the union
      return variableUnion;
    });
}
