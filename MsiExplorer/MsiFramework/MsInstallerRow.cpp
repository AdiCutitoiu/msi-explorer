#include "stdafx.h"
#include "MsInstallerRow.h"
#include "MsInstallerRowRecord.h"

MsInstallerRow::MsInstallerRow()
  : mRowHandle(0)
{
}

MsInstallerRow::MsInstallerRow(MSIHANDLE aRowHandle)
  : mRowHandle(aRowHandle)
{
  UINT fieldSize = ::MsiRecordGetFieldCount(mRowHandle);
  mRecords.reserve(fieldSize);

  for (UINT fieldNumber = 1; fieldNumber <= fieldSize; ++fieldNumber)
    mRecords.push_back(MsInstallerRowRecord(aRowHandle, fieldNumber));
}

MsInstallerRowRecord MsInstallerRow::operator[](int aIndex)
{
  if (aIndex < 0 || UINT(aIndex) >= mRecords.size())
  {
    assert(!"Invalid record");
  }

  return mRecords[aIndex];
}

UINT MsInstallerRow::GetFieldNumber()
{
  return mRecords.size();
}

std::vector<MsInstallerRowRecord>::iterator MsInstallerRow::begin()
{
  return mRecords.begin();
}

std::vector<MsInstallerRowRecord>::iterator MsInstallerRow::end()
{
  return mRecords.end();
}
