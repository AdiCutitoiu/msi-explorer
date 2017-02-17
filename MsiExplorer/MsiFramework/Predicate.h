#pragma once
#include "Expression.h"
#include "VariableExpression.h"

class Predicate : public Expression
{
public:
  /**
   * Default constructor, the string predicate is the empty string
   */
  Predicate();

  /**
   * @param aExpression the expression from which the string predicate is built
   */
  explicit Predicate(const shared_ptr<Expression> & aExpression);

  /**
   * @brief Sets the comparison value of a variable used only once.
   */
  void SetVariable(const wstring & aVariableName, const wstring & aVariableValue);

  /**
   * @returns a SQL predicate in wstring format
   */
  wstring Get() const;

protected:
  /**
   * @brief Dummy
   */
  virtual std::wstring BuildCondition() const override;

  /**
   * @brief Dummy
   */
  virtual std::map<wstring, Expression *> BuildVariableMap() override;

private:
  shared_ptr<Expression> mExpression;  // starting expression for building the predicate
  std::map<wstring, VariableExpression *> mVariableMap;  // variable map(all mExpression variables)
};
