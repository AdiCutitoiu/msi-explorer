#include "stdafx.h"
#include "Predicate.h"

Predicate::Predicate()
{
}

Predicate::Predicate(const shared_ptr<Expression> & aExpression)
  : mExpression(aExpression)
{
  auto varMap = Expression::CallBuildVariableMap(mExpression.get());

  // Down casting all the variables from Expression to VariableExpression
  transform(varMap.begin(),
            varMap.end(),
            inserter(mVariableMap, mVariableMap.begin()),
            [](const auto & aVarPair) {
              return make_pair(aVarPair.first, dynamic_cast<VariableExpression *>(aVarPair.second));
            });
}

void Predicate::SetVariable(const wstring & aVariableName, const wstring & aVariableValue)
{
  auto found = mVariableMap.find(aVariableName);

  if (found != mVariableMap.end())
  {
    // setting the value
    found->second->SetValue(aVariableValue);
  }
}

wstring Predicate::Get() const
{
  // return empty string if the predicate has no variables
  return mVariableMap.empty() ? L"" : L"WHERE " + Expression::CallBuildCondition(mExpression.get());
}

/*virtual*/ std::wstring Predicate::BuildCondition() const
{
  return wstring();
}

/*virtual*/ std::map<wstring, Expression *> Predicate::BuildVariableMap()
{
  return map<wstring, Expression *>();
}
