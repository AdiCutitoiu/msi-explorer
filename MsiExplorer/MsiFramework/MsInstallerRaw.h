#pragma once

#include "MsInstallerRawRecord.h"

class MsInstallerRaw
{
public:
  friend class MsInstallerTable;

  MsInstallerRaw(MSIHANDLE aRawHandle, const std::vector<std::wstring> & aColumnNames);

  MsInstallerRawRecord operator[](int aIndex);

  UINT GetFieldNumber();

private:
  MSIHANDLE                         mRawHandle;
  std::vector<MsInstallerRawRecord> mRecords;
};
