#pragma once
#include "MsInstallerTableSchema.h"
#include "MsInstallerView.h"

class MsInstallerTable
{
public:
  MsInstallerTable(MSIHANDLE aDatabaseHandle, const std::wstring & aTableName);

  UINT GetRowNumber() const;

  bool InsertRow(const MsInstallerRecord & aRecord);

  MsInstallerTableSchema GetTableSchema() const;

  std::vector<std::wstring> GetColumnNames() const;

  bool UpdateRow(const MsInstallerRecord & aRecord);

  MsInstallerView GetView(const std::vector<std::wstring> & aColumns = { L"*" }) const;

private:
  std::map<std::wstring, int> FindPrimaryKeyFields() const;

  bool IsPrimaryKeyMatch(const MsInstallerRecord & aFirst,
                         const MsInstallerRecord & aSecond,
                         const std::map<std::wstring, int> & aFields) const;

  MSIHANDLE    mDatabaseHandle;
  std::wstring mTableName;
};