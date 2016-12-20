#pragma once

class Msi
{
public:
  Msi(MSIHANDLE aSession);

  Msi(const std::wstring & aMsiPath);

  ~Msi();

  std::wstring GetProperty(const std::wstring & aPropertyName);

  void SetProperty(const std::wstring & aPropertyName, const std::wstring & aPropertyValue);

private:
  MSIHANDLE mSession;
  bool      mOpenByHandle = false;
};