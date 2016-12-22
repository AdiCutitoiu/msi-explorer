#pragma once

#include "MsInstallerRowRecord.h"

class MsInstallerRow
{
public:
  friend class MsInstallerTable;

  MsInstallerRow();
  MsInstallerRow(MSIHANDLE aRowHandle);

  MsInstallerRowRecord operator[](int aIndex);

  UINT GetFieldNumber();

  std::vector<MsInstallerRowRecord>::iterator begin();

  std::vector<MsInstallerRowRecord>::iterator end();

private:
  MSIHANDLE                         mRowHandle;
  std::vector<MsInstallerRowRecord> mRecords;
};
