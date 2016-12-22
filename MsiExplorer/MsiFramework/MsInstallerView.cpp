#include "stdafx.h"
#include "MsInstallerView.h"

namespace Utility
{
MsInstallerView::MsInstallerView(MSIHANDLE aDatabase, const std::wstring & aQuery)
  : mWasExecuted(false)
{
  mView  = 0;
  auto x = ::MsiDatabaseOpenView(aDatabase, aQuery.c_str(), &mView);
}

pair<bool, MsInstallerRow> MsInstallerView::Fetch()
{
  MSIHANDLE record = 0;
  if (!mWasExecuted)
  {
    ::MsiViewExecute(mView, record);
    mWasExecuted = true;
  }

  UINT state = ::MsiViewFetch(mView, &record);

  return state == ERROR_SUCCESS ? make_pair(true, MsInstallerRow(record))
                                : make_pair(false, MsInstallerRow());
}
vector<wstring> MsInstallerView::GetColumnNames()
{
  MSIHANDLE rowHandle = 0;
  ::MsiViewExecute(mView, rowHandle);
  ::MsiViewFetch(mView, &rowHandle);
  ::MsiViewGetColumnInfo(mView, MSICOLINFO_NAMES, &rowHandle);

  MsInstallerRow row(rowHandle);

  vector<wstring> result(row.GetFieldNumber());
  transform(row.begin(), row.end(), result.begin(),
            [](const auto & aRecord) { return aRecord.Get(); });

  return result;
}
MsInstallerView::~MsInstallerView()
{
  MsiCloseHandle(mView);
}
}