#include "stdafx.h"
#include "MsInstallerCell.h"

MsInstallerCell::MsInstallerCell(const wstring & aData)
  : mData(aData)
{
}

std::wstring MsInstallerCell::Get() const
{
  return mData;
}

void MsInstallerCell::Set(const wstring & aData)
{
  mData = aData;
}
