#pragma once
#include "MsInstallerRow.h"

namespace Utility
{
class MsInstallerView
{
public:
  MsInstallerView(MSIHANDLE aDatabase, const std::wstring & aQuery);

  pair<bool, MsInstallerRow> Fetch();

  vector<MsInstallerRow> FetchAll();

  std::vector<std::wstring> GetColumnNames();

  ~MsInstallerView();

private:
  MSIHANDLE      mView;
  bool           mFinished;
  MsInstallerRow mCurrentRow;
};
}