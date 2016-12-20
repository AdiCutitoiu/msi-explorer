#pragma once

class MsiTable
{
public:
  friend class MsInstallerDatabase;

private:
  MsiTable(const wstring & aTableName, MSIHANDLE aDatabaseHandle);

  vector<wstring> mColumnNames;
};