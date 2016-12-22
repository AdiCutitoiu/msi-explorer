#include "stdafx.h"
#include "MsInstallerTable.h"
#include "MsInstallerView.h"

wstring MsInstallerTable::GetName() const
{
  return mName;
}

std::vector<std::wstring> MsInstallerTable::GetColumnNames() const
{
  wstring query = L"SELECT * FROM " + mName;

  Utility::MsInstallerView view(mDatabase, query.c_str());

  return view.GetColumnNames();
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

  auto rawReceived = view.Fetch();
  while (rawReceived.first)
  {
    mRows.push_back(rawReceived.second);
    rawReceived = view.Fetch();
  }

  int x = 2;
}