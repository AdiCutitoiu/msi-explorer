#include "stdafx.h"
#include "MsiPropertyGetterSetter.h"

namespace MsiPropertyGetterSetter {
  wstring Get(MSIHANDLE aSession, const wstring & aPropertyName)
  {
    DWORD valueBuffer = 0;

    ::MsiGetProperty(aSession, aPropertyName.c_str(), TEXT(""), &valueBuffer);

    wstring result(valueBuffer, L' ');
    ++valueBuffer;

    ::MsiGetProperty(aSession, aPropertyName.c_str(), &result[0], &valueBuffer);

    return result;
  }

  void Set(MSIHANDLE       aSession,
    const wstring & aPropertyName,
    const wstring & aPropertyValue)
  {
    ::MsiSetProperty(aSession, aPropertyValue.c_str(), aPropertyValue.c_str());
  }
}