#pragma once

class MsInstallerTable
{
public:
  friend class MsInstallerDatabase;

  std::wstring GetName() const;

private:
  MsInstallerTable(const std::wstring & aTableName, MSIHANDLE aDatabaseHandle);

  std::vector<std::wstring> mColumnNames;
  std::wstring              mName;
};