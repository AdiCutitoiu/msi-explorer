#include "stdafx.h"
#include "MsInstallerDatabase.h"
#include "ColumnSelector.h"

MsInstallerDatabase::MsInstallerDatabase(MSIHANDLE aMsiHandle)
  : mDatabaseHandle(::MsiGetActiveDatabase(aMsiHandle))
{
}

MsInstallerDatabase::MsInstallerDatabase(const std::wstring & aMsiPath)
{
  MSIHANDLE handle = 0;
  ::MsiOpenDatabase(aMsiPath.c_str(), MSIDBOPEN_TRANSACT, &handle);

  mDatabaseHandle = Utility::DatabaseHandle(handle);
}

std::vector<std::wstring> MsInstallerDatabase::GetTableNames() const
{
  vector<wstring> tableNames;

  MsInstallerView view(mDatabaseHandle, L"_Tables", ColumnSelector({ L"Name" }));

  auto fetched = view.GetNext();
  while (fetched.first)
  {
    auto record = fetched.second;

    auto name = record.GetCell(0).Get();

    tableNames.push_back(name);

    fetched = view.GetNext();
  }

  return tableNames;
}

MsInstallerTable MsInstallerDatabase::GetTable(const wstring & aTableName) const
{
  vector<wstring> tableNames = GetTableNames();

  bool isFound = find(tableNames.begin(), tableNames.end(), aTableName) != tableNames.end();
  assert(isFound && "Table not found");

  return MsInstallerTable(mDatabaseHandle, aTableName);
}

MsInstallerTableSchema MsInstallerDatabase::GetTableSchema(const std::wstring & aTableName) const
{
  return MsInstallerTableSchema(mDatabaseHandle, aTableName);
}

bool MsInstallerDatabase::CommitChanges()
{
  return ::MsiDatabaseCommit(mDatabaseHandle) == ERROR_SUCCESS;
}
