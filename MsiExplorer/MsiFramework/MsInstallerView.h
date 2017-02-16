#pragma once

#include "ColumnSelector.h"
#include "DatabaseHandle.h"
#include "MsInstallerCell.h"
#include "MsInstallerRecord.h"
#include "MsInstallerTableSchema.h"
#include "Predicate.h"

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
  MsInstallerView(Utility::DatabaseHandle aDatabaseHandle,
                  const std::wstring &    aTableName,
                  const ColumnSelector &  aColumnSelector = ColumnSelector(),
                  const Predicate &       aPredicate      = Predicate());

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
   * A call to GetNext after the bool in the return is false will cause another execution of the
   * view.
   *
   * @returns a pair consisting of a bool(true if the view has not finished yet) and the next record
   *
   */
  std::pair<bool, MsInstallerRecord> GetNext();

  /**
   * @returns a vector containing the names of the columns, or {L"*"} if no specific column was
   * requested
   */
  vector<wstring> GetColumnNames() const;

private:
  enum class State  // the state of the view
  {
    UNINITIALIZED,
    NOT_FINISHED,
    FINISHED
  };

  /**
   * @brief updates the current handle with the information in a record
   *
   * @param aRecord the record which contains the information to update the current handle
   */
  void UpdateCurrentHandle(const MsInstallerRecord & aRecord);

  /**
   * @brief executes the view
   */
  void Execute();

  Utility::DatabaseHandle mDatabaseHandle;       // handle to the database
  MSIHANDLE               mViewHandle;           // the view handle
  MSIHANDLE               mCurrentRecordHandle;  // a handle to the last fetched record
  State                   mState;                // the state of this view
  vector<wstring>         mColumnNames;          // the column names of the view
};
