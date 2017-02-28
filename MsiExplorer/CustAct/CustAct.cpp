// CustAct.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../MsiFramework/MsInstallerDatabase.h"
#include "../MsiFramework/MsiUtility.h"
#include "../MsiFramework/OrExpression.h"

UINT WINAPI DoStuff(MSIHANDLE aSession)
{
  ::MessageBox(NULL, TEXT("I am a cust act message box"), TEXT("Cust Act"), MB_OK);

  MsInstallerDatabase db(aSession);

  auto table = db.GetTable(L"Control");
  auto var   = make_shared<VariableExpression>(L"Type", L"Text");
  auto var2  = make_shared<VariableExpression>(L"Type", L"PushButton");
  auto orExp = make_shared<OrExpression>(var, var2);
  auto pred  = Predicate(orExp);
  auto view  = table.GetView(ColumnSelector(), Predicate(orExp));

  vector<MsInstallerRecord> toModify;

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    toModify.push_back(fetched.second);

    auto res = view.DeleteCurrent();
  }

  for (auto & modRecord : toModify)
  {
    auto record = modRecord;
    record[9].Set(MsiUtility::FormatField(aSession, record, 9));
    record[9].Set(MsiUtility::FormatField(aSession, record, 9));

    record[9].Set(L'[' + to_wstring(record[9].Get().size()) + L']' + modRecord[9].Get());

    bool success = view.InsertTemporary(record);
  }

  db.CommitChanges();

  return ERROR_SUCCESS;
}
