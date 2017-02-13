#include "stdafx.h"
#include "MsInstallerTableSchema.h"
#include "RecordFieldStringGetter.h"

MsInstallerTableSchema::MsInstallerTableSchema(MSIHANDLE                         aDatabaseHandle,
                                               const std::wstring &              aTableName,
                                               const std::vector<std::wstring> & aColumnNames)
{
  wstring columns = accumulate(aColumnNames.begin(), aColumnNames.end(), wstring(),
                               [](const wstring & aResult, const wstring & aColumnName) {
                                 return aResult == L"" ? aColumnName : aResult + L',' + aColumnName;
                               });

  wstring query = L"SELECT " + columns + L" FROM " + aTableName;

  MSIHANDLE view   = 0;
  MSIHANDLE record = 0;
  ::MsiDatabaseOpenView(aDatabaseHandle, query.c_str(), &view);
  ::MsiViewExecute(view, record);

  MSIHANDLE columnTypes = 0;
  MSIHANDLE columnNames = 0;
  ::MsiViewGetColumnInfo(view, MSICOLINFO::MSICOLINFO_NAMES, &columnNames);
  ::MsiViewGetColumnInfo(view, MSICOLINFO::MSICOLINFO_TYPES, &columnTypes);

  int fieldSize = MsiRecordGetFieldCount(columnTypes);
  for (int i = 1; i <= fieldSize; ++i)
  {
    mColumns.emplace_back(RecordFieldStringGetter::Get(columnNames, i),
                          RecordFieldStringGetter::Get(columnTypes, i), false, false);
  }

  MarkPrimaryKeys(aDatabaseHandle, aTableName);
  MarkNullableColumns(aDatabaseHandle, aTableName);
}

std::vector<wstring> MsInstallerTableSchema::GetColumnNames() const
{
  vector<wstring> result(mColumns.size());

  transform(mColumns.begin(), mColumns.end(), result.begin(),
            [](const auto & aColumn) { return get<0>(aColumn); });

  return result;
}

std::wstring MsInstallerTableSchema::GetColumnType(const std::wstring & aColumnName) const
{
  auto found = find_if(mColumns.begin(), mColumns.end(),
                       [&](const auto & aColumn) { return get<ID_COLUMN_NAME>(aColumn) == aColumnName; });

  return get<ID_COLUMN_TYPE>(*found);
}

std::vector<wstring> MsInstallerTableSchema::GetColumnTypes() const
{
  vector<wstring> result(mColumns.size());

  transform(mColumns.begin(), mColumns.end(), result.begin(),
            [](const auto & aColumn) { return get<ID_COLUMN_TYPE>(aColumn); });

  return result;
}

std::vector<std::wstring> MsInstallerTableSchema::GetPrimaryKeyColumns() const
{
  vector<ColumnAttributes> primaryKeyColumns;
  copy_if(mColumns.begin(), mColumns.end(), back_inserter(primaryKeyColumns),
          [](const auto & aColumn) { return get<ID_NULLABLE>(aColumn); });

  vector<wstring> result(primaryKeyColumns.size());
  transform(primaryKeyColumns.begin(), primaryKeyColumns.end(), result.begin(),
            [](const auto & aColumn) { return get<ID_COLUMN_NAME>(aColumn); });

  return result;
}

bool MsInstallerTableSchema::IsPrimaryKey(const wstring & aColumnName) const
{
  auto found = find_if(mColumns.begin(), mColumns.end(),
                       [&](const auto & aColumn) { return get<ID_COLUMN_NAME>(aColumn) == aColumnName; });

  return get<ID_NULLABLE>(*found);
}

bool MsInstallerTableSchema::IsNullable(const wstring & aColumnName) const
{
  auto found = find_if(mColumns.begin(), mColumns.end(),
                       [&](const auto & aColumn) { return get<ID_COLUMN_NAME>(aColumn) == aColumnName; });

  return get<ID_PRIMARY_KEY>(*found);
}

void MsInstallerTableSchema::MarkPrimaryKeys(MSIHANDLE aDatabaseHandle, const wstring & aTableName)
{
  MSIHANDLE record = 0;
  ::MsiDatabaseGetPrimaryKeys(aDatabaseHandle, aTableName.c_str(), &record);

  int             fieldSize = MsiRecordGetFieldCount(record);
  vector<wstring> primaryKeys;
  for (int i = 0; i < fieldSize; ++i)
  {
    primaryKeys.emplace_back(RecordFieldStringGetter::Get(record, i));
  }

  for (auto & column : mColumns)
  {
    if (find(primaryKeys.begin(), primaryKeys.end(), get<ID_COLUMN_NAME>(column)) != primaryKeys.end())
      get<ID_NULLABLE>(column) = true;
  }

  MsiCloseHandle(record);
}

void MsInstallerTableSchema::MarkNullableColumns(MSIHANDLE       aDatabaseHandle,
                                                 const wstring & aTableName)
{
  wstring query =
    L"SELECT Column FROM _Validation WHERE `Nullable`='Y' AND `Table`='" + aTableName + L'\'';

  MSIHANDLE view   = 0;
  MSIHANDLE record = 0;
  ::MsiDatabaseOpenView(aDatabaseHandle, query.c_str(), &view);
  ::MsiViewExecute(view, record);

  vector<wstring> nullableCols;
  while (::MsiViewFetch(view, &record) == ERROR_SUCCESS)
  {
    nullableCols.push_back(RecordFieldStringGetter::Get(record, 1));

    MsiCloseHandle(record);
  }

  for (auto & column : mColumns)
  {
    if (find(nullableCols.begin(), nullableCols.end(), get<ID_COLUMN_NAME>(column)) != nullableCols.end())
    {
      get<ID_PRIMARY_KEY>(column) = true;
    }
  }

  MsiCloseHandle(view);
}
