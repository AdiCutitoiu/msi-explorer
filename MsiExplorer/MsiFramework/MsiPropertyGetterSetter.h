#pragma once

class MsiPropertyGetterSetter
{
public:
  static wstring Get(MSIHANDLE aSession, const wstring & aPropertyName);

  static void Set(MSIHANDLE       aSession,
                  const wstring & aPropertyName,
                  const wstring & aPropertyValue);
};