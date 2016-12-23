#pragma once

#include "MsInstallerRow.h"

class MsInstallerTable
{
public:
  friend class MsInstallerDatabase;

  std::wstring GetName() const;

  std::vector<std::wstring> GetColumnNames() const;

  std::vector<std::wstring> GetColumnTypes() const;

  std::vector<std::wstring> GetPrimaryKeys() const;

  UINT GetRowNumber();

  std::vector<MsInstallerRow>::iterator begin();

  std::vector<MsInstallerRow>::iterator end();

private:
  MsInstallerTable(const std::wstring & aTableName, MSIHANDLE aDatabaseHandle);

  MSIHANDLE                   mDatabase;
  std::wstring                mName;
  std::vector<MsInstallerRow> mRows;
  std::vector<std::wstring>   mColumnNames;
  std::vector<std::wstring>   mColumnTypes;
  std::vector<std::wstring>   mPrimaryKeys;
};