#include "stdafx.h"
#include "MsInstaller.h"
#include "MsInstallerDatabase.h"
#include "MsiPropertyGetterSetter.h"

#define RUNNING_MSI_PATH_PROP TEXT("OriginalDatabase")

MsInstaller::MsInstaller(MSIHANDLE aSession)
  : mSession(aSession)
  , mOpenByHandle(true)
  , mMsiPath(GetProperty(RUNNING_MSI_PATH_PROP))
{
}

MsInstaller::MsInstaller(const wstring & aMsiPath)
  : mSession(0)
  , mMsiPath(aMsiPath)
{
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
  return mOpenByHandle ? MsInstallerDatabase(mSession) : MsInstallerDatabase(mMsiPath);
}
