// MsiToXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../MsiFramework/MsInstallerDatabase.h"

int main()
{
  /*
  MSIHANDLE hand = 0;
  UINT uiStatus = ::MsiOpenDatabase(TEXT("C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi"),
  MSIDBOPEN_TRANSACT, &hand);

  if (uiStatus == ERROR_SUCCESS)
  {
    std::cout << "Opened successfully\n";

    MSIHANDLE view = 0;
    auto result = MsiDatabaseOpenView(hand, TEXT("SELECT Dialog,Width,Height FROM Dialog"), &view);

    MSIHANDLE record = 0;
    result = MsiViewExecute(view, record);

    while (MsiViewFetch(view, &record) == ERROR_SUCCESS)
    {
      UINT nrFields = MsiRecordGetFieldCount(record);

      for (int i = 1; i <= nrFields; i++)
      {
        TCHAR name[256];
        DWORD buffer = DWORD(256);
        MsiRecordGetString(record, i, name, &buffer);

        std::wcout << name << ' ';
      }
      std::cout << '\n';
    }
  }
  else
  {
    std::cout << "Not opened successfully\n";
  }

  ::MsiCloseHandle(hand);
  */

  MsInstallerDatabase db(L"C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi");
  auto                table = db.GetTable(L"Dialog");
  auto schema = table.GetTableSchema();

  auto view = table.GetView();

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    std::wcout << fetched.second[0].Get() << L'\n';
  }

  std::wcout << endl;

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    std::wcout << fetched.second[0].Get() << L'\n';
  }
  
  return 0;
}
