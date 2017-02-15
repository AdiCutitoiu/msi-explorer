#pragma once

class Expression
{
public:
  virtual std::wstring Get() const = 0;

  virtual std::map<wstring, Expression*> GetVariables() = 0;
};