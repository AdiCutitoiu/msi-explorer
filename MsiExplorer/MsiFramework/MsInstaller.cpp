#include "stdafx.h"
#include "MsInstaller.h"
#include "MsiPropertyGetterSetter.h"

Msi::Msi(MSIHANDLE aSession)
  : mSession(aSession)
  , mOpenByHandle(true)
{
}

Msi::Msi(const wstring & aMsiPath)
{
  ::MsiOpenPackage(aMsiPath.c_str(), &mSession);
}

Msi::~Msi()
{
  if (!mOpenByHandle)
    ::MsiCloseHandle(mSession);
}

wstring Msi::GetProperty(const wstring & aPropertyName)
{
  return MsiPropertyGetterSetter::Get(mSession, aPropertyName);
}

void Msi::SetProperty(const std::wstring & aPropertyName, const std::wstring & aPropertyValue)
{
  MsiPropertyGetterSetter::Set(mSession, aPropertyName, aPropertyValue);
}
