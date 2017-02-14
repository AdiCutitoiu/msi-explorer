#pragma once

class MsInstallerTableSchema
{
public:
  using ColumnName       = std::wstring;
  using ColumnType       = std::wstring;
  using Nullable         = bool;
  using PrimaryKey       = bool;
  using ColumnAttributes = std::tuple<std::wstring, std::wstring, bool, bool>;

  enum ID // enum column attribute IDs
  {
    ID_COLUMN_NAME = 0,
    ID_COLUMN_TYPE = 1,
    ID_NULLABLE = 2,
    ID_PRIMARY_KEY = 3
  };

  /**
   * @brief Constructs a table schema for a given table in the database for specified columns
   *
   * @param aDatabaseHandle handle to the database
   *
   * @param aTableName the name of the table
   *
   * @param aColumnNames specified column names
   */
  MsInstallerTableSchema(MSIHANDLE                         aDatabaseHandle,
                         const std::wstring &              aTableName,
                         const std::vector<std::wstring> & aColumnNames = { L"*" });

  /**
   * @returns the names of the columns
   */
  vector<std::wstring> GetColumnNames() const;

  /**
   * @returns the type of a column
   *
   * @param aColumnName the name of the column
   */
  std::wstring GetColumnType(const std::wstring & aColumnName) const;

  /**
   * @returns a vector consisting of the types of all the columns
   */
  std::vector<std::wstring> GetColumnTypes() const;

  /**
   * @returns the name of the columns which are primary keys
   */
  std::vector<std::wstring> GetPrimaryKeyColumns() const;

  /**
   * @returns true if a specified column is a primary key
   *
   * @param aColumnName the name of the column
   */
  bool IsPrimaryKey(const std::wstring & aColumnName) const;

  /**
   * @returns true if a specified column is nullable
   *
   * @param aColumnName the name of the column
   */
  bool IsNullable(const std::wstring & aColumnName) const;

  /**
   * @returns a vector containing the attributes of all columns
   */
  vector<ColumnAttributes> GetColumnAttributes() const;

private:
  /**
   * @brief marks the primary keys in mColumns(sets PrimaryKey in ColumnAttributes to true)
   */
  void MarkPrimaryKeys(MSIHANDLE aDatabaseHandle, const std::wstring & aTableName);

  /**
   * @brief marks the nullable columns in mColumns(sets Nullable in ColumnAttributes to true)
   */
  void MarkNullableColumns(MSIHANDLE aDatabaseHandle, const std::wstring & aTableName);

  std::vector<ColumnAttributes> mColumns; // vector of column attributes
};
