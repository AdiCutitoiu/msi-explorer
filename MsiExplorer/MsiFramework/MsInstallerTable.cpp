#include "stdafx.h"
#include "MsInstallerTable.h"

MsInstallerTable::MsInstallerTable(const Utility::DatabaseHandle aDatabaseHandle,
                                   const std::wstring &          aTableName)
  : mDatabaseHandle(aDatabaseHandle)
  , mTableName(aTableName)
{
}

UINT MsInstallerTable::GetRowCount() const
{
  MsInstallerView view(mDatabaseHandle, mTableName);
  view.Execute();

  UINT counter = 0;
  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    ++counter;
  }

  return counter;
}

wstring MsInstallerTable::GetName() const
{
  return mTableName;
}

bool MsInstallerTable::InsertRow(const MsInstallerRecord & aRecord)
{
  MsInstallerView view(mDatabaseHandle, mTableName);

  return view.Insert(aRecord);
}

MsInstallerTableSchema MsInstallerTable::GetTableSchema() const
{
  return MsInstallerTableSchema(mDatabaseHandle, mTableName);
}

vector<std::wstring> MsInstallerTable::GetColumnNames() const
{
  return MsInstallerTableSchema(mDatabaseHandle, mTableName).GetColumnNames();
}

bool MsInstallerTable::UpdateRow(const MsInstallerRecord & aRecord)
{
  MsInstallerView view(mDatabaseHandle, mTableName);
  view.Execute();

  auto fetched = view.GetNext();
  while (fetched.first)
  {
    std::map<wstring, int> primaryKeyFields = FindPrimaryKeyFields();

    if (IsPrimaryKeyMatch(aRecord, fetched.second, primaryKeyFields))
    {
      return view.UpdateCurrent(aRecord);
    }

    fetched = view.GetNext();
  }

  return false;
}

MsInstallerView MsInstallerTable::GetView(
  const std::vector<std::wstring> & aColumns /*= { L"*" }*/) const
{
  return MsInstallerView(mDatabaseHandle, mTableName);
}

map<wstring, int> MsInstallerTable::FindPrimaryKeyFields() const
{
  auto schema = GetTableSchema();

  auto columns           = schema.GetColumnNames();
  auto primaryKeyColumns = schema.GetPrimaryKeyColumns();

  map<wstring, int> fields;
  transform(columns.begin(), columns.end(), inserter(fields, fields.begin()),
            [&](auto & aColumnName) {
              return make_pair(aColumnName, distance(&columns[0], &aColumnName));
            });

  map<wstring, int> primaryKeyFields;
  copy_if(fields.begin(), fields.end(), inserter(primaryKeyFields, primaryKeyFields.begin()),
          [&](const pair<wstring, int> & aField) {
            bool isFound = find(primaryKeyColumns.begin(), primaryKeyColumns.end(), aField.first) !=
                           primaryKeyColumns.end();

            return isFound;
          });

  return primaryKeyFields;
}

bool MsInstallerTable::IsPrimaryKeyMatch(const MsInstallerRecord & aFirst,
                                         const MsInstallerRecord & aSecond,
                                         const std::map<std::wstring, int> & aFields) const
{
  for (const auto & field : aFields)
  {
    int fieldNr = field.second;

    wstring firstValue  = aFirst.GetCell(fieldNr).Get();
    wstring secondValue = aSecond.GetCell(fieldNr).Get();

    if (firstValue != secondValue)
    {
      return false;
    }
  }

  return true;
}
