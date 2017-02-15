#include "stdafx.h"
#include "MultipleExpression.h"

MultipleExpression::MultipleExpression(vector<unique_ptr<Expression>> aExpressions)
  : mExpressions(move(aExpressions))
{
}

std::map<wstring, Expression*> MultipleExpression::GetVariables()
{
  // build a map containing all the variables used in this expression
  return accumulate(mExpressions.begin(), mExpressions.end(), map<wstring, Expression*>(),
                    [](const map<wstring, Expression*> & aPrevResult, unique_ptr<Expression> & aExpression)
                    {
                       map<wstring, Expression*> variableUnion;

                       auto currentVariables = aExpression->GetVariables();

                      
                       set_union(aPrevResult.begin(), aPrevResult.end(),
                                 currentVariables.begin(), currentVariables.end(),
                                 inserter(variableUnion, variableUnion.begin()));

                       return variableUnion;
                    });
}
