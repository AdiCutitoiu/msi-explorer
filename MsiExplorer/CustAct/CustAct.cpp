// CustAct.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../MsiFramework/MsInstallerDatabase.h"
#include "../MsiFramework/OrExpression.h"

UINT WINAPI DoStuff(MSIHANDLE aSession)
{
  ::MessageBox(NULL, TEXT("I am a cust act message box"), TEXT("Cust Act"), MB_OK);

  MsInstallerDatabase db(aSession);

  auto table = db.GetTable(L"Control2");
  auto var   = make_shared<VariableExpression>(L"Type", L"Text");
  auto var2  = make_shared<VariableExpression>(L"Type", L"PushButton");
  auto orExp = make_shared<OrExpression>(var, var2);
  auto pred  = Predicate(orExp);
  pred.SetVariable(L"Type", L"Combobox");
  auto view = table.GetView(ColumnSelector(), Predicate(orExp));

  vector<MsInstallerRecord> toModify;

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    toModify.push_back(fetched.second);

    auto res = view.DeleteCurrent();
  }

  for (auto & modRecord : toModify)
  {
    auto content = modRecord[9].Get();

    modRecord[9].Set(L'[' + to_wstring(content.size()) + L']' + content);

    bool success = view.InsertTemporary(modRecord);
  }

  db.CommitChanges();

  return ERROR_SUCCESS;
}
