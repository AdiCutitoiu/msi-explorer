#pragma once

#include "MsInstallerCell.h"
#include "MsInstallerRecord.h"
#include "MsInstallerTableSchema.h"

class MsInstallerView
{
public:
  MsInstallerView(MSIHANDLE                         aDatabaseHandle,
                  const std::wstring &              aTableName,
                  const std::vector<std::wstring> & aTableColumns);

  void Execute();

  bool UpdateCurrent(const MsInstallerRecord & aRecord);

  pair<bool, MsInstallerRecord> GetNext();

private:
  enum class State
  {
    UNINITIALIZED,
    NOT_FINISHED,
    FINISHED
  };

  void UpdateCurrentHandle(const MsInstallerRecord & aRecord);

  MSIHANDLE mViewHandle;
  MSIHANDLE mCurrentRecordHandle;
  State     mState;
};