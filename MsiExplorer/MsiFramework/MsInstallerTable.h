#pragma once
#include "DatabaseHandle.h"
#include "MsInstallerTableSchema.h"
#include "MsInstallerView.h"

class MsInstallerTable
{
public:
  /**
   * @brief Constructs a table object
   *
   * @param aDatabaseHandle a handle to the database in which the table should be found
   *
   * @param aTableName the name of the table
   */
  MsInstallerTable(const Utility::DatabaseHandle aDatabaseHandle, const std::wstring & aTableName);

  /**
   * @returns the number of rows
   */
  UINT GetRowCount() const;

  /**
   * @returns the name of the table
   */
  std::wstring GetName() const;

  /**
   * @brief Inserts a row into this table
   *
   * @param aRecord the row to be inserted
   *
   * @returns true if the record was successfully inserted
   */
  bool InsertRow(const MsInstallerRecord & aRecord);

  /**
   * @returns the schema of this table
   */
  MsInstallerTableSchema GetTableSchema() const;

  /**
   * @returns the names of the columns of this table
   */
  std::vector<std::wstring> GetColumnNames() const;

  /**
   * @brief Updates a row. Finds the row using the primary keys of this table.
   *
   * @returns true if the row was successfully updates
   */
  bool UpdateRow(const MsInstallerRecord & aRecord);

  /**
   * @returns a view to this table
   *
   * @param aColumns the columns requested in the view
   */
  MsInstallerView GetView(const std::vector<std::wstring> & aColumns = { L"*" }) const;

private:
  /**
   * @returns a map consisting of pairs <pkColumnName, index> where
   *  pkColumnName is the name of a primary key column
   *  index is the position of the column in the table columns
   */
  std::map<std::wstring, int> FindPrimaryKeyFields() const;

  /**
   * @returns true if two records have the same primary keys
   *
   * @param aFirst the first record
   *
   * @param aSecond the second record
   *
   * @param aFields primary key column names with their corresponding position
   */
  bool IsPrimaryKeyMatch(const MsInstallerRecord & aFirst,
                         const MsInstallerRecord & aSecond,
                         const std::map<std::wstring, int> & aFields) const;

  Utility::DatabaseHandle mDatabaseHandle;  // handle to the database of this table
  std::wstring            mTableName;       // name of this table
};