#pragma once

#include "MsInstallerRaw.h"

class MsInstallerTable
{
public:
  friend class MsInstallerDatabase;

  std::wstring GetName() const;

  std::vector<std::wstring> GetColumnNames() const;

  MsInstallerRaw & operator[](int aRawNumber);

private:
  MsInstallerTable(const std::wstring & aTableName, MSIHANDLE aDatabaseHandle);

  MSIHANDLE                   mDatabase;
  std::wstring                mName;
  std::vector<MsInstallerRaw> mRaws;
};