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
wstring FormatString(MSIHANDLE aSession, wstring aString)
{
  DWORD valueBuffer = 0;

  auto tempRecord = ::MsiCreateRecord(1);
  ::MsiRecordSetString(aSession, 0, aString.c_str());

  ::MsiFormatRecord(aSession, tempRecord, TEXT(""), &valueBuffer);

  wstring result(valueBuffer, L' ');
  ++valueBuffer;

  ::MsiFormatRecord(aSession, tempRecord, &result[0], &valueBuffer);
  ::MsiCloseHandle(tempRecord);

  return result;
}
}
