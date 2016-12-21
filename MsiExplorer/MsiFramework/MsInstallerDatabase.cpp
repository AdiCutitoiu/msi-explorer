#include "stdafx.h"
#include "MsInstallerDatabase.h"
#include "MsInstallerTable.h"

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
    name.pop_back();

    if (name[0] != L'#')
      mTables.emplace_back(MsInstallerTable(name, mDatabaseHandle));
  }

  sort(mTables.begin(), mTables.end(), [](const auto & aFirst, const auto & aSecond) {
    return aFirst.GetName() < aSecond.GetName();
  });
}

MsInstallerDatabase::MsInstallerDatabase(const std::wstring & aMsiPath)
{
  ::MsiOpenDatabase(aMsiPath.c_str(), MSIDBOPEN_READONLY, &mDatabaseHandle);

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
    name.pop_back();

    if (name[0] != L'#')
      mTables.emplace_back(MsInstallerTable(name, mDatabaseHandle));
  }

  sort(mTables.begin(), mTables.end(), [](const auto & aFirst, const auto & aSecond) {
    return aFirst.GetName() < aSecond.GetName();
  });
}

std::vector<std::wstring> MsInstallerDatabase::GetTableNames() const
{
  vector<wstring> names(mTables.size());

  transform(mTables.begin(), mTables.end(), names.begin(),
            [](const auto & aTable) { return aTable.GetName(); });

  return names;
}

MsInstallerTable MsInstallerDatabase::GetTable(const wstring & aTableName) const
{
  auto found = lower_bound(
    mTables.begin(), mTables.end(), aTableName,
    [](const auto & aTable, const auto & aTableName) { return aTable.GetName() < aTableName; });

  auto tableName = found->GetName();

  if (found == mTables.end() || found->GetName() != aTableName)
    assert(!"Table not found");

  return *found;
}

MsInstallerDatabase::~MsInstallerDatabase()
{
  MsiCloseHandle(mDatabaseHandle);
}
