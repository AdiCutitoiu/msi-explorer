#pragma once

#include "MsInstallerCell.h"
#include "RecordFieldStringGetter.h"

class MsInstallerRecord
{
public:
  MsInstallerRecord() = default;

  MsInstallerRecord(const std::vector<std::wstring> aCellsValues);

  MsInstallerRecord(MSIHANDLE aRecordHandle);

  MsInstallerCell & operator[](int aIndex);

  UINT GetFieldNumber() const;

  MsInstallerCell GetField(int aIndex) const;

  std::vector<MsInstallerCell>::iterator begin();

  std::vector<MsInstallerCell>::iterator end();

private:
  std::vector<MsInstallerCell> mCells;
};
