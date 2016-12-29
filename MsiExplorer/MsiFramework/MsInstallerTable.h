#pragma once
#include "MsInstallerTableSchema.h"
#include "MsInstallerView.h"

class MsInstallerTable
{
public:
  MsInstallerTable(MSIHANDLE aDatabaseHandle, const std::wstring & aTableName);

  UINT GetRowNumber() const;

  bool InsertRow(const MsInstallerRecord & aRecord) const;

  MsInstallerTableSchema GetTableSchema() const;

  std::vector<std::wstring> GetColumnNames() const;

  bool UpdateRow(const std::wstring & aRecord) const;

  MsInstallerView GetView() const;

private:
  MSIHANDLE mDatabaseHandle;
  wstring   mTableName;
};