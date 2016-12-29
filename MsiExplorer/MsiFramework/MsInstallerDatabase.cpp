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

// std::vector<std::wstring> MsInstallerDatabase::GetTableNames() const
// {
//   vector<wstring> names (mTables.size());
//
//   transform(mTables.begin(), mTables.end(), names.begin(),
//             [](const auto & aTable) { return aTable.GetName(); });
//
//   return names;
// }

// MsInstallerTable MsInstallerDatabase::GetTable(const wstring & aTableName) const
// {
//   auto found = lower_bound(
//     mTables.begin(), mTables.end(), aTableName,
//     [](const auto & aTable, const auto & aTableName) { return aTable.GetName() < aTableName; });
//
//   auto tableName = found->GetName();
//
//   if (found == mTables.end() || found->GetName() != aTableName)
//     assert(!"Table not found");
//
//   return *found;
// }

MsInstallerTableSchema MsInstallerDatabase::GetTableSchema(const std::wstring & aTableName) const
{
  return MsInstallerTableSchema(mDatabaseHandle, aTableName);
}

MsInstallerDatabase::~MsInstallerDatabase()
{
  MsiCloseHandle(mDatabaseHandle);
}
