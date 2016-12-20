#pragma once

class MsInstallerDatabase
{
public:
  ~MsInstallerDatabase();

  friend class MsInstaller;

private:
  MsInstallerDatabase(MSIHANDLE aMsiHandle);

  MSIHANDLE                 mDatabaseHandle;
  std::vector<std::wstring> mTableNames;
};
