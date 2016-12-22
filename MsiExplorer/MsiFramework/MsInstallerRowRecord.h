#pragma once

class MsInstallerRowRecord
{
public:
  friend class MsInstallerRow;

  std::wstring Get() const;

  void Set(const std::wstring & aValue);

private:
  MsInstallerRowRecord(MSIHANDLE aRowHandle, int aFieldNumber);

  MSIHANDLE mRowHandle;
  int       mFieldNumber;
};
