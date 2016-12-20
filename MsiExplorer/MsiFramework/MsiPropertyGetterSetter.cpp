#include "stdafx.h"
#include "MsiPropertyGetterSetter.h"

wstring MsiPropertyGetterSetter::Get(MSIHANDLE aSession, const wstring & aPropertyName)
{
  DWORD valueBuffer = 0;

  MsiGetProperty(aSession, aPropertyName.c_str(), TEXT(""), &valueBuffer);

  wstring result(valueBuffer, L' ');
  ++valueBuffer;

  MsiGetProperty(aSession, aPropertyName.c_str(), &result[0], &valueBuffer);

  return result;
}

void MsiPropertyGetterSetter::Set(MSIHANDLE       aSession,
                                  const wstring & aPropertyName,
                                  const wstring & aPropertyValue)
{
  auto st = MsiSetProperty(aSession, aPropertyValue.c_str(), aPropertyValue.c_str());
  ERROR_SUCCESS;
}
