#include "stdafx.h"
#include "MsInstallerRawRecord.h"

std::wstring MsInstallerRawRecord::Get() const
{
  DWORD buffSize = 0;
  ::MsiRecordGetString(mRawHandle, 1, L"", &buffSize);

  ++buffSize;
  wstring name(buffSize, ' ');
  ::MsiRecordGetString(mRawHandle, 1, &name[0], &buffSize);
  name.pop_back();

  return name;
}

void MsInstallerRawRecord::Set(const wstring & aValue)
{
  ::MsiRecordSetString(mRawHandle, mFieldNumber, aValue.c_str());
}

MsInstallerRawRecord::MsInstallerRawRecord(MSIHANDLE aRawHandle, int aFieldNumber)
  : mRawHandle(aRawHandle)
  , mFieldNumber(aFieldNumber)
{
}