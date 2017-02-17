#pragma once
#include "stdafx.h"
#include "Expression.h"

class MultipleExpression : public Expression
{
public:
  /**
   * @param aFirst left AND operand
   *
   * @param aSecond right AND operand
   */
  template <typename T>
  MultipleExpression(const shared_ptr<Expression> & aFirst, const shared_ptr<T> & aSecond);

  /**
   * @param aExpression left AND operand
   *
   * @param aArgs right AND operands
   */
  template <typename... Args>
  MultipleExpression(const shared_ptr<Expression> & aExpression, const shared_ptr<Args> &... aArgs);

protected:
  std::map<wstring, Expression *> BuildVariableMap() override;

  list<shared_ptr<Expression>> mExpressions;  // list of operands
};

template <typename... Args>
inline MultipleExpression::MultipleExpression(const shared_ptr<Expression> & aExpression,
                                              const shared_ptr<Args> &... aArgs)
  : MultipleExpression(std::forward<const shared_ptr<Args> &>(aArgs)...)
{
  mExpressions.push_front(aExpression);
}

template <typename T>
MultipleExpression::MultipleExpression(const shared_ptr<Expression> & aFirst,
                                       const shared_ptr<T> &          aSecond)
{
  mExpressions.push_front(aSecond);
  mExpressions.push_front(aFirst);
}

/*virtual*/ std::map<wstring, Expression *> MultipleExpression::BuildVariableMap()
{
  // build a map containing all the variables used in this expression
  return accumulate(
    mExpressions.begin(),
    mExpressions.end(),
    map<wstring, Expression *>(),
    [](const map<wstring, Expression *> & aPrevResult, shared_ptr<Expression> & aExpression) {
      map<wstring, Expression *> variableUnion;

      // get current variables
      auto currentVariables = Expression::CallBuildVariableMap(aExpression.get());
      // auto currentVariables = std::bind(&MultipleExpression::BuildVariableMap,
      // aExpression.get())();

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
