#pragma once

#include "MsInstallerTable.h"

class MsInstallerDatabase
{
public:
  MsInstallerDatabase(MSIHANDLE aMsiHandle);
  MsInstallerDatabase(const std::wstring & aMsiPath);

  std::vector<std::wstring> GetTableNames() const;

  MsInstallerTable GetTable(const std::wstring & aTableName) const;

  ~MsInstallerDatabase();

private:
  void ReadTables();

  MSIHANDLE                     mDatabaseHandle;
  std::vector<MsInstallerTable> mTables;
};
