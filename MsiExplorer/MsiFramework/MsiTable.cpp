#include "stdafx.h"
#include "MsiTable.h"

MsiTable::MsiTable(const wstring & aTableName, MSIHANDLE aDatabaseHandle)
{
  MSIHANDLE view  = 0;
  wstring   query = L"SELECT * FROM " + aTableName;
  ::MsiDatabaseOpenView(aDatabaseHandle, query.c_str(), &view);

  MSIHANDLE record = 0;
  //::MsiViewExecute(view, record);

  if (MsiViewGetColumnInfo(view, MSICOLINFO_NAMES, &record) == ERROR_SUCCESS)
  {
    UINT nrFields = MsiRecordGetFieldCount(record);

    mColumnNames.reserve(nrFields);

    for (int i = 1; i <= nrFields; ++i)
    {
      DWORD buffSize = 0;
      MsiRecordGetString(record, i, L"", &buffSize);

      ++buffSize;
      wstring name(buffSize, ' ');
      MsiRecordGetString(record, i, &name[0], &buffSize);

      mColumnNames.push_back(name);
    }
  }
}