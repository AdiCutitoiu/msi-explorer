#pragma once

#include "MsInstallerTable.h"

class MsInstallerDatabase
{
public:
  friend class MsInstaller;

  std::vector<std::wstring> GetTableNames() const;

  MsInstallerTable GetTable(const std::wstring & aTableName) const;

  ~MsInstallerDatabase();

private:
  MsInstallerDatabase(MSIHANDLE aMsiHandle);

  MSIHANDLE                     mDatabaseHandle;
  std::vector<MsInstallerTable> mTables;
};
