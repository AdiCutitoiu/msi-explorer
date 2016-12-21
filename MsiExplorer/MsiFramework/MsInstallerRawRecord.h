#pragma once

class MsInstallerRawRecord
{
public:
  friend class MsInstallerRaw;

  std::wstring Get() const;

  void Set(const std::wstring & aValue);

private:
  MsInstallerRawRecord(MSIHANDLE aRawHandle, int aFieldNumber);

  MSIHANDLE mRawHandle;
  int       mFieldNumber;
};
