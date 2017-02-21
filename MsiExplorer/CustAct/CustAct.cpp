// CustAct.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../MsiFramework/MsInstallerDatabase.h"

UINT WINAPI DoStuff(MSIHANDLE aSession)
{
  ::MessageBox(NULL, TEXT("I am a cust act message box"), TEXT("Cust Act"), MB_OK);

  MsInstallerDatabase db(aSession);

  auto table = db.GetTable(L"Control");
  auto var   = make_shared<VariableExpression>(L"Type", L"Text");
  auto view  = table.GetView(ColumnSelector(), Predicate(var));

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
