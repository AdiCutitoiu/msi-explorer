#pragma once

#include "DatabaseHandle.h"
#include "MsInstallerTable.h"
#include "MsInstallerTableSchema.h"

class MsInstallerDatabase
{
public:
  /**
   * Constructs a MsiInstallerDatabase given a handle to the msi installer(will open the database)
   */
  MsInstallerDatabase(MSIHANDLE aMsiHandle);

  /**
   * Constructs a MsiInstallerDatabase given a path to a msi file.
   */
  MsInstallerDatabase(const std::wstring & aMsiPath);

  /**
   * @returns the names of the tables in the database
   */
  std::vector<std::wstring> GetTableNames() const;

  /**
   * @returns a MsInstallerTable object for manipulating a specific table
   *
   * @param aTableName the name of the requested table
   */
  MsInstallerTable GetTable(const std::wstring & aTableName) const;

  /**
   * @returns the schema of a certain table
   *
   * @param aTableName the name of the requested table
   */
  MsInstallerTableSchema GetTableSchema(const std::wstring & aTableName) const;

  /**
   * @brief Commits the changes made to the database
   *
   * @returns true if the changes were successfully committed
   */
  bool CommitChanges();

private:
  Utility::DatabaseHandle mDatabaseHandle;  // a handle to the database
};
