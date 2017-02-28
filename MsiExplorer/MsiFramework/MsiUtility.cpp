#include "stdafx.h"
#include "MsiUtility.h"

namespace MsiUtility
{
wstring GetProperty(MSIHANDLE aSession, const wstring & aPropertyName)
{
  DWORD valueBuffer = 0;

  ::MsiGetProperty(aSession, aPropertyName.c_str(), TEXT(""), &valueBuffer);

  wstring result(valueBuffer, L' ');
  ++valueBuffer;

  ::MsiGetProperty(aSession, aPropertyName.c_str(), &result[0], &valueBuffer);

  return result;
}

void SetProperty(MSIHANDLE aSession, const wstring & aPropertyName, const wstring & aPropertyValue)
{
  ::MsiSetProperty(aSession, aPropertyValue.c_str(), aPropertyValue.c_str());
}
wstring FormatField(MSIHANDLE aSession, const MsInstallerRecord & aRecord, int aFieldNumber)
{
  MSIHANDLE record = ::MsiCreateRecord(aRecord.GetFieldNumber());

  for (int i = 1; i <= aRecord.GetFieldNumber(); i++)
  {
    ::MsiRecordSetString(record, i, aRecord[i - 1].Get().c_str());
  }
  ::MsiRecordSetString(record, 0, aRecord[aFieldNumber].Get().c_str());

  DWORD valueBuffer = 0;
  ::MsiFormatRecord(aSession, record, TEXT(""), &valueBuffer);
  wstring result(valueBuffer, L' ');
  ++valueBuffer;
  ::MsiFormatRecord(aSession, record, &result[0], &valueBuffer);

  return result;
}
}
