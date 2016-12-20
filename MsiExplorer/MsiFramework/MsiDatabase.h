#pragma once

#include "MsiTableView.h"

class MsiDatabase
{
public:
  // MsiDatabase(const wstring & aMsiPath);
  //
  // MsiTableView OpenView(const wstring & aQuery);
  //
  // wstring GetProperty(const wstring & aPropertyName);
  // void SetProperty(const wstring & aPropertyName, const wstring & aPropertyValue);
  //
  // bool IsOpen();
  //
  //~MsiDatabase();

private:
  MSIHANDLE mMsiHandle;
  bool      mIsOpen;
};
