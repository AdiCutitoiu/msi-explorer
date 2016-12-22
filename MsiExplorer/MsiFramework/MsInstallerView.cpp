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

vector<MsInstallerRow> MsInstallerView::FetchAll()
{
  vector<MsInstallerRow> allRows;

  auto fetched = Fetch();
  while (fetched.first)
  {
    allRows.push_back(fetched.second);
    fetched = Fetch();
  }

  return allRows;
}

vector<wstring> MsInstallerView::GetColumnNames() const
{
  return GetColumnNamesTypes(true);
}

std::vector<std::wstring> MsInstallerView::GetColumnTypes() const
{
  return GetColumnNamesTypes(false);
}

MsInstallerView::~MsInstallerView()
{
  MsiCloseHandle(mView);
}
std::vector<std::wstring> MsInstallerView::GetColumnNamesTypes(bool aGetNames) const
{
  MSIHANDLE rowHandle         = 0;
  auto      informationNeeded = aGetNames ? MSICOLINFO_NAMES : MSICOLINFO_TYPES;
  ::MsiViewGetColumnInfo(mView, informationNeeded, &rowHandle);

  MsInstallerRow row(rowHandle);

  vector<wstring> result(row.GetFieldNumber());
  transform(row.begin(), row.end(), result.begin(),
            [](const auto & aRecord) { return aRecord.Get(); });

  return result;
}
}