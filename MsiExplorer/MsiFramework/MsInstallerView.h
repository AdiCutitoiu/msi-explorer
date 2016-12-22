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

  std::vector<std::wstring> GetColumnNames() const;

  std::vector<std::wstring> GetColumnTypes() const;

  ~MsInstallerView();

private:
  std::vector<std::wstring> GetColumnNamesTypes(bool aGetNames) const;

  MSIHANDLE      mView;
  bool           mFinished;
  MsInstallerRow mCurrentRow;
};
}