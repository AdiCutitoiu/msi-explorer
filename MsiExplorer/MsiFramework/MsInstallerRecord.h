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
  const MsInstallerCell & operator[](int aIndex) const;

  UINT GetFieldNumber() const;

  MsInstallerCell GetCell(int aIndex) const;

  void SetCell(int aIndex, const MsInstallerCell & aCell);

  std::vector<MsInstallerCell>::iterator begin();

  std::vector<MsInstallerCell>::iterator end();

private:
  std::vector<MsInstallerCell> mCells;
};
