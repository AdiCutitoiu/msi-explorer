#include "stdafx.h"
#include "MsInstallerDatabase.h"
#include "MsInstallerTable.h"
#include "MsInstallerView.h"

MsInstallerDatabase::MsInstallerDatabase(MSIHANDLE aMsiHandle)
{
  mDatabaseHandle = ::MsiGetActiveDatabase(aMsiHandle);

  ReadTables();
}

MsInstallerDatabase::MsInstallerDatabase(const std::wstring & aMsiPath)
{
  ::MsiOpenDatabase(aMsiPath.c_str(), MSIDBOPEN_READONLY, &mDatabaseHandle);

  // ReadTables();
}

void MsInstallerDatabase::ReadTables()
{
  auto view = Utility::MsInstallerView(mDatabaseHandle, TEXT("SELECT Name FROM _Tables"));

  for (auto & fetched : view.FetchAll())
  {
    wstring tableName = fetched[0].Get();

    mTables.push_back(MsInstallerTable(tableName, mDatabaseHandle));
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

MsInstallerTableSchema MsInstallerDatabase::GetTableSchema(const std::wstring & aTableName) const
{
  return MsInstallerTableSchema(mDatabaseHandle, aTableName);
}

MsInstallerDatabase::~MsInstallerDatabase()
{
  MsiCloseHandle(mDatabaseHandle);
}
