#include "stdafx.h"
#include "MsInstaller.h"
#include "MsInstallerDatabase.h"
#include "MsiPropertyGetterSetter.h"

MsInstaller::MsInstaller(MSIHANDLE aSession)
  : mSession(aSession)
  , mOpenByHandle(true)
{
}

MsInstaller::MsInstaller(const wstring & aMsiPath)
{
  ::MsiOpenPackage(aMsiPath.c_str(), &mSession);
}

MsInstaller::~MsInstaller()
{
  if (!mOpenByHandle)
    ::MsiCloseHandle(mSession);
}

wstring MsInstaller::GetProperty(const wstring & aPropertyName)
{
  return MsiPropertyGetterSetter::Get(mSession, aPropertyName);
}

void MsInstaller::SetProperty(const std::wstring & aPropertyName,
                              const std::wstring & aPropertyValue)
{
  MsiPropertyGetterSetter::Set(mSession, aPropertyName, aPropertyValue);
}

MsInstallerDatabase MsInstaller::OpenDatabase()
{
  return MsInstallerDatabase(mSession);
}
