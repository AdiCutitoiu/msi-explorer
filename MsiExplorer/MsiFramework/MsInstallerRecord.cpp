#include "stdafx.h"
#include "MsInstallerRecord.h"
#include "MsInstallerCell.h"

MsInstallerRecord::MsInstallerRecord(const std::vector<std::wstring> aCellsValues)
{
  transform(aCellsValues.begin(), aCellsValues.end(), back_inserter(mCells),
    [](const auto & aCellValue) { return MsInstallerCell(aCellValue); });
}

MsInstallerRecord::MsInstallerRecord(MSIHANDLE aRecordHandle)
{
  int fieldSize = ::MsiRecordGetFieldCount(aRecordHandle);

  mCells.reserve(fieldSize);
  for (int field = 1; field <= fieldSize; ++field)
  {
    wstring value = RecordFieldStringGetter::Get(aRecordHandle, field);

    mCells.push_back(MsInstallerCell(value));
  }
}

MsInstallerCell & MsInstallerRecord::operator[](int aIndex)
{
  if (aIndex < 0 || UINT(aIndex) >= mCells.size())
  {
    assert(!"Invalid record");
  }

  return mCells[aIndex];
}

const MsInstallerCell & MsInstallerRecord::operator[](int aIndex) const
{
  if (aIndex < 0 || UINT(aIndex) >= mCells.size())
  {
    assert(!"Invalid record");
  }

  return mCells[aIndex];
}

UINT MsInstallerRecord::GetFieldNumber() const
{
  return mCells.size();
}

MsInstallerCell MsInstallerRecord::GetCell(int aIndex) const
{
  if (aIndex < 0 || UINT(aIndex) >= mCells.size())
  {
    assert(!"Invalid record");
  }

  return mCells[aIndex];
}

void MsInstallerRecord::SetCell(int aIndex, const MsInstallerCell & aCell)
{
  mCells[aIndex] = aCell;
}

std::vector<MsInstallerCell>::iterator MsInstallerRecord::begin()
{
  return mCells.begin();
}

std::vector<MsInstallerCell>::iterator MsInstallerRecord::end()
{
  return mCells.end();
}

std::vector<MsInstallerCell>::const_iterator MsInstallerRecord::cbegin() const
{
  return mCells.cbegin();
}

std::vector<MsInstallerCell>::const_iterator MsInstallerRecord::cend() const
{
  return mCells.cend();
}