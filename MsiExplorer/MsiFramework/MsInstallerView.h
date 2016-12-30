#pragma once

#include "DatabaseHandle.h"
#include "MsInstallerCell.h"
#include "MsInstallerRecord.h"
#include "MsInstallerTableSchema.h"

class MsInstallerView
{
public:
  MsInstallerView(Utility::DatabaseHandle           aDatabaseHandle,
                  const std::wstring &              aTableName,
                  const std::vector<std::wstring> & aTableColumns = { L"*" });

  void Execute();

  bool UpdateCurrent(const MsInstallerRecord & aRecord);

  bool Insert(const MsInstallerRecord & aRecord);

  std::pair<bool, MsInstallerRecord> GetNext();

private:
  enum class State
  {
    UNINITIALIZED,
    NOT_FINISHED,
    FINISHED
  };

  void UpdateCurrentHandle(const MsInstallerRecord & aRecord);

  Utility::DatabaseHandle mDatabaseHandle;
  MSIHANDLE               mViewHandle;
  MSIHANDLE               mCurrentRecordHandle;
  State                   mState;
};
