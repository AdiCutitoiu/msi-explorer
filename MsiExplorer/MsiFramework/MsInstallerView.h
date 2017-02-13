#pragma once

#include "DatabaseHandle.h"
#include "MsInstallerCell.h"
#include "MsInstallerRecord.h"
#include "MsInstallerTableSchema.h"

class MsInstallerView
{
public:
  /**
   * @brief Constructs a view to a table in the database
   *
   * @param aDatabaseHandle handle to the database
   *
   * @param aTableName name of the table
   *
   * @param aTableColumns a vector specifying the columns in the view
   */
  MsInstallerView(Utility::DatabaseHandle           aDatabaseHandle,
                  const std::wstring &              aTableName,
                  const std::vector<std::wstring> & aTableColumns = { L"*" });

  /**
   * @brief executes the view
   */
  void Execute();

  /**
   * @brief updates the current record with aRecord
   *
   * @param aRecord the record
   */
  bool UpdateCurrent(const MsInstallerRecord & aRecord);

  /**
   * @brief inserts a record into the table
   *
   * @param aRecord the record to be inserted
   */
  bool Insert(const MsInstallerRecord & aRecord);

  /**
   * @returns a pair consisting of a bool(true if the view has not finished yet) and the next record
   */
  std::pair<bool, MsInstallerRecord> GetNext();

private:
  enum class State  // the state of the view
  {
    UNINITIALIZED,
    NOT_FINISHED,
    FINISHED
  };

  /**
   * 
   */
  void UpdateCurrentHandle(const MsInstallerRecord & aRecord);

  Utility::DatabaseHandle mDatabaseHandle;      // handle to the database
  MSIHANDLE               mViewHandle;          // the view handle
  MSIHANDLE               mCurrentRecordHandle; // a handle to the last fetched record
  State                   mState;               // the state of this view
};
