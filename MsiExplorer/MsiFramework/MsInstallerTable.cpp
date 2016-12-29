#include "stdafx.h"
#include "MsInstallerTable.h"

UINT MsInstallerTable::GetRowNumber() const
{
  MsInstallerView view(mDatabaseHandle, mTableName);
  view.Execute();

  UINT counter = 0;
  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    ++counter;
  }

  return counter;
}
