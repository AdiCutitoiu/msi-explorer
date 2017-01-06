#pragma once
#include "DatabaseHandle.h"
#include "MsInstallerTableSchema.h"
#include "MsInstallerView.h"

class MsInstallerTable
{
public:
  MsInstallerTable(const Utility::DatabaseHandle aDatabaseHandle, const std::wstring & aTableName);

  UINT GetRowCount() const;

  std::wstring GetName() const;

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

  Utility::DatabaseHandle mDatabaseHandle;
  std::wstring            mTableName;
};