#pragma once

class MsInstallerTableSchema
{
public:
  using ColumnAttributes = std::tuple<std::wstring, std::wstring, bool, bool>;

  MsInstallerTableSchema(MSIHANDLE                         aDatabaseHandle,
                         const std::wstring &              aTableName,
                         const std::vector<std::wstring> & aColumnNames = { L"*" });

  std::vector<std::wstring> GetColumnNames() const;

  std::wstring GetColumnType(const std::wstring & aColumnName) const;

  std::vector<std::wstring> GetColumnTypes() const;

  std::vector<std::wstring> GetPrimaryKeyColumns() const;

  bool IsPrimaryKey(const std::wstring & aColumnName) const;

  bool IsNullable(const std::wstring & aColumnName) const;

private:
  void MarkPrimaryKeys(MSIHANDLE aDatabaseHandle, const std::wstring & aTableName);

  void MarkNullableColumns(MSIHANDLE aDatabaseHandle, const std::wstring & aTableName);

  MSIHANDLE                     aViewHandle;
  std::vector<ColumnAttributes> mColumns;
};
