#include "stdafx.h"
#include "MsInstallerTable.h"
#include "MsInstallerView.h"

wstring MsInstallerTable::GetName() const
{
  return mName;
}

std::vector<std::wstring> MsInstallerTable::GetColumnNames() const
{
  return mColumnNames;
}

std::vector<std::wstring> MsInstallerTable::GetColumnTypes() const
{
  return mColumnTypes;
}

std::vector<std::wstring> MsInstallerTable::GetPrimaryKeys() const
{
  return mPrimaryKeys;
}

MsInstallerRow & MsInstallerTable::operator[](int aRowNumber)
{
  if (UINT(aRowNumber) >= mRows.size())
    assert(!"Invalid row");

  return mRows[aRowNumber];
}

UINT MsInstallerTable::GetRowNumber()
{
  return mRows.size();
}

std::vector<MsInstallerRow>::iterator MsInstallerTable::begin()
{
  return mRows.begin();
}

std::vector<MsInstallerRow>::iterator MsInstallerTable::end()
{
  return mRows.end();
}

MsInstallerTable::MsInstallerTable(const wstring & aTableName, MSIHANDLE aDatabaseHandle)
  : mName(aTableName)
  , mDatabase(aDatabaseHandle)
{
  wstring query = L"SELECT * FROM " + mName;

  Utility::MsInstallerView view(mDatabase, query.c_str());

  mRows        = view.FetchAll();
  mColumnNames = view.GetColumnNames();
  mColumnTypes = view.GetColumnTypes();

  MSIHANDLE rowHandle = 0;
  ::MsiDatabaseGetPrimaryKeys(mDatabase, mName.c_str(), &rowHandle);
  auto row = MsInstallerRow(rowHandle);

  transform(row.begin(), row.end(), back_inserter(mPrimaryKeys),
            [](const auto & aRecord) { return aRecord.Get(); });
}