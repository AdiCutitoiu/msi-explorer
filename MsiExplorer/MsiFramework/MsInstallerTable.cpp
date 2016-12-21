#include "stdafx.h"
#include "MsInstallerTable.h"

wstring MsInstallerTable::GetName() const
{
  return mName;
}

std::vector<std::wstring> MsInstallerTable::GetColumnNames() const
{
  MSIHANDLE view  = 0;
  wstring   query = L"SELECT * FROM " + mName;
  ::MsiDatabaseOpenView(mDatabase, query.c_str(), &view);

  MSIHANDLE record = 0;
  //::MsiViewExecute(view, record);

  vector<wstring> columnNames;
  if (MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &record) == ERROR_SUCCESS)
  {
    UINT nrFields = MsiRecordGetFieldCount(record);

    columnNames.reserve(nrFields);

    for (UINT i = 1; i <= nrFields; ++i)
    {
      DWORD buffSize = 0;
      ::MsiRecordGetString(record, i, L"", &buffSize);

      ++buffSize;
      wstring name(buffSize, ' ');
      ::MsiRecordGetString(record, i, &name[0], &buffSize);
      name.pop_back();

      columnNames.push_back(name);
    }
  }

  return columnNames;
}

MsInstallerRaw & MsInstallerTable::operator[](int aRawNumber)
{
  if (aRawNumber >= mRaws.size())
    assert(!"Invalid row");

  return mRaws[aRawNumber];
}

UINT MsInstallerTable::GetRawNumber()
{
  return mRaws.size();
}

MsInstallerTable::MsInstallerTable(const wstring & aTableName, MSIHANDLE aDatabaseHandle)
  : mName(aTableName)
  , mDatabase(aDatabaseHandle)
{
  MSIHANDLE view  = 0;
  wstring   query = L"SELECT * FROM " + mName;
  ::MsiDatabaseOpenView(mDatabase, query.c_str(), &view);

  MSIHANDLE record = 0;
  ::MsiViewExecute(view, record);

  vector<wstring> columnNames;
  while (MsiViewFetch(view, &record) == ERROR_SUCCESS)
  {
    mRaws.push_back(MsInstallerRaw(record, GetColumnNames()));
  }
}