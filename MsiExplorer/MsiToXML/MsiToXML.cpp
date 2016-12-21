// MsiToXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../MsiFramework/MsInstaller.h"
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

  // MsiDatabase db(L"C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi");

  // Msi(L"C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi");

  MsInstaller msi(L"C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi");

  MsInstallerDatabase db = msi.OpenDatabase();

  auto table = db.GetTable(L"TextStyle");

  for (int i = 0; i < table.GetRawNumber(); ++i)
  {
    auto raw = table[i];
    for (int fieldNr = 0; fieldNr < raw.GetFieldNumber(); ++fieldNr)
      std::wcout << raw[fieldNr].Get() << ' ';
    std::cout << std::endl;
  }

  return 0;
}
