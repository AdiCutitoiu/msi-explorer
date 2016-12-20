#include "stdafx.h"
#include "MsiDatabase.h"

// MsiDatabase::MsiDatabase(const wstring & aMsiPath)
//  : mMsiHandle(0)
//  , mIsOpen(false)
//{
//  mIsOpen = ::MsiOpenDatabase(aMsiPath.c_str(), MSIDBOPEN_TRANSACT, &mMsiHandle) == ERROR_SUCCESS;
//}
//
// bool MsiDatabase::IsOpen()
//{
//  return mIsOpen;
//}
//
// MsiDatabase::~MsiDatabase()
//{
//  ::MsiCloseHandle(mMsiHandle);
//}
