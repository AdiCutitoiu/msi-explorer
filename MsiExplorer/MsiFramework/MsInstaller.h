#pragma once

#include "MsInstallerDatabase.h"

class MsInstaller
{
public:
  MsInstaller(MSIHANDLE aSession);

  MsInstaller(const std::wstring & aMsiPath);

  std::wstring GetProperty(const std::wstring & aPropertyName);

  void SetProperty(const std::wstring & aPropertyName, const std::wstring & aPropertyValue);

  MsInstallerDatabase OpenDatabase();

private:
  MSIHANDLE    mSession;
  bool         mOpenByHandle = false;
  std::wstring mMsiPath;
};