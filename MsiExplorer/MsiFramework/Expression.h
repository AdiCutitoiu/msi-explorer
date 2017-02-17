#pragma once

class Expression
{
protected:
  /**
   * @returns a condition string for this expression
   */
  virtual std::wstring BuildCondition() const = 0;

  /**
   * Caller for virtual function GetVariables()
   */
  static std::map<wstring, Expression *> CallBuildVariableMap(Expression * aExpression);

  /**
   * Caller for virtual function BuildCondition
   */
  static std::wstring CallBuildCondition(const Expression * aExpression);

  /**
   * @returns a variable map <name, varPtr>
   */
  virtual std::map<wstring, Expression *> BuildVariableMap() = 0;
};
