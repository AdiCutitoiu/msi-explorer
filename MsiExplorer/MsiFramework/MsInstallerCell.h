#pragma once

class MsInstallerCell
{
public:
  MsInstallerCell(const std::wstring & aData);

  std::wstring Get() const;

  void Set(const std::wstring & aData);

private:
  std::wstring mData;
};
