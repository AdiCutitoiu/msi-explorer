#pragma once

#include "MsInstallerRawRecord.h"

class MsInstallerRaw
{
public:
  friend class MsInstallerTable;

  MsInstallerRaw(MSIHANDLE aViewHandle, const std::vector<std::wstring> & aColumnNames);

private:
  MSIHANDLE                         aRawHandle;
  std::vector<MsInstallerRawRecord> mRecords;
};
