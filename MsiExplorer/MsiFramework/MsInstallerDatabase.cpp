#include "stdafx.h"
#include "MsInstallerDatabase.h"

MsInstallerDatabase::MsInstallerDatabase(MSIHANDLE aMsiHandle)
{
  mDatabaseHandle = ::MsiGetActiveDatabase(aMsiHandle);

  MSIHANDLE view = 0;
  ::MsiDatabaseOpenView(mDatabaseHandle, TEXT("SELECT Name FROM _Tables"), &view);

  MSIHANDLE record = 0;
  ::MsiViewExecute(view, record);

  while (::MsiViewFetch(view, &record) == ERROR_SUCCESS)
  {
    DWORD buffSize = 0;
    MsiRecordGetString(record, 1, L"", &buffSize);

    ++buffSize;
    wstring name(buffSize, ' ');
    MsiRecordGetString(record, 1, &name[0], &buffSize);

    mTableNames.push_back(name);
  }

  sort(mTableNames.begin(), mTableNames.end());

  int x = 0;
}

MsInstallerDatabase::~MsInstallerDatabase()
{
  MsiCloseHandle(mDatabaseHandle);
}
