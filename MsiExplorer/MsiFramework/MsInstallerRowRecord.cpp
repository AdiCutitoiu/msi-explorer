#include "stdafx.h"
#include "MsInstallerRowRecord.h"

std::wstring MsInstallerRowRecord::Get() const
{
  DWORD buffSize = 0;
  ::MsiRecordGetString(mRowHandle, mFieldNumber, L"", &buffSize);

  ++buffSize;
  wstring name(buffSize, ' ');
  ::MsiRecordGetString(mRowHandle, mFieldNumber, &name[0], &buffSize);
  name.pop_back();

  return name;
}

void MsInstallerRowRecord::Set(const wstring & aValue)
{
  ::MsiRecordSetString(mRowHandle, mFieldNumber, aValue.c_str());
}

MsInstallerRowRecord::MsInstallerRowRecord(MSIHANDLE aRowHandle, int aFieldNumber)
  : mRowHandle(aRowHandle)
  , mFieldNumber(aFieldNumber)
{
}