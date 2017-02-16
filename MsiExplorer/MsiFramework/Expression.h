#pragma once

class Expression
{
protected:
  virtual std::wstring BuildCondition() const = 0;

  /**
   * Caller for virtual function GetVariables()
   */
  static std::map<wstring, Expression *> CallBuildVariableMap(Expression * aExpression);

  /**
   * Caller for virtual function BuildCondition
   */
  static std::wstring CallBuildCondition(const Expression * aExpression);

  virtual std::map<wstring, Expression *> BuildVariableMap() = 0;
};
