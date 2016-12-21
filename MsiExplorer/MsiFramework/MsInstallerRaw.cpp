#include "stdafx.h"
#include "MsInstallerRaw.h"
#include "MsInstallerRawRecord.h"

MsInstallerRaw::MsInstallerRaw(MSIHANDLE aRawHandle, const vector<wstring> & aColumnNames)
  : mRawHandle(aRawHandle)
{
  mRecords.reserve(aColumnNames.size());
  for (UINT fieldNumber = 1; fieldNumber <= aColumnNames.size(); ++fieldNumber)
    mRecords.push_back(MsInstallerRawRecord(aRawHandle, fieldNumber));
}

MsInstallerRawRecord MsInstallerRaw::operator[](int aIndex)
{
  if (aIndex < 0 || aIndex >= mRecords.size())
  {
    assert(!"Invalid record");
  }

  return mRecords[aIndex];
}

UINT MsInstallerRaw::GetFieldNumber()
{
  return mRecords.size();
}
