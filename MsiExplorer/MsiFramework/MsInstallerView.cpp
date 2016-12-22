#include "stdafx.h"
#include "MsInstallerView.h"

namespace Utility
{
MsInstallerView::MsInstallerView(MSIHANDLE aDatabase, const std::wstring & aQuery)
{
  mView  = 0;
  auto x = ::MsiDatabaseOpenView(aDatabase, aQuery.c_str(), &mView);

  MSIHANDLE rowHandle = 0;
  ::MsiViewExecute(mView, rowHandle);

  if (::MsiViewFetch(mView, &rowHandle) == ERROR_SUCCESS)
  {
    mFinished   = false;
    mCurrentRow = MsInstallerRow(rowHandle);
  }
}

pair<bool, MsInstallerRow> MsInstallerView::Fetch()
{
  auto result = make_pair(!mFinished, mCurrentRow);

  MSIHANDLE record = 0;
  mFinished        = !(::MsiViewFetch(mView, &record) == ERROR_SUCCESS);

  mCurrentRow = mFinished ? MsInstallerRow() : MsInstallerRow(record);

  return result;
}

vector<wstring> MsInstallerView::GetColumnNames()
{
  MSIHANDLE rowHandle = 0;
  ::MsiViewGetColumnInfo(mView, MSICOLINFO_NAMES, &rowHandle);

  MsInstallerRow row(rowHandle);

  vector<wstring> result(row.GetFieldNumber());
  transform(row.begin(), row.end(), result.begin(),
            [](const auto & aRecord) { return aRecord.Get(); });

  return result;
}

MsInstallerView::~MsInstallerView()
{
  // MsiCloseHandle(mView);
}
}