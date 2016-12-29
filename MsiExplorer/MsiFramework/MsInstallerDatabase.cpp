#include "stdafx.h"
#include "MsInstallerDatabase.h"

MsInstallerDatabase::MsInstallerDatabase(MSIHANDLE aMsiHandle)
{
  mDatabaseHandle = ::MsiGetActiveDatabase(aMsiHandle);
}

MsInstallerDatabase::MsInstallerDatabase(const std::wstring & aMsiPath)
{
  ::MsiOpenDatabase(aMsiPath.c_str(), MSIDBOPEN_TRANSACT, &mDatabaseHandle);
}

std::vector<std::wstring> MsInstallerDatabase::GetTableNames() const
{
  vector<wstring> tableNames;

  MsInstallerView view(mDatabaseHandle, L"_Tables", { L"Name" });
  view.Execute();

  auto fetched = view.GetNext();
  while (fetched.first)
  {
    auto record = fetched.second;

    auto name = record.GetField(1).Get();

    tableNames.push_back(name);
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

MsInstallerDatabase::~MsInstallerDatabase()
{
  MsiCloseHandle(mDatabaseHandle);
}
