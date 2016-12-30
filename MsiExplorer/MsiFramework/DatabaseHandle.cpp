#include "stdafx.h"
#include "DatabaseHandle.h"

namespace Utility
{
DatabaseHandle::DatabaseHandle(MSIHANDLE aDatabaseHandle)
  : mDbHandlePtr(new MSIHANDLE(aDatabaseHandle),
                 [](MSIHANDLE * aDatabaseHandle) { ::MsiCloseHandle(*aDatabaseHandle); })
{
}
DatabaseHandle::operator MSIHANDLE() const
{
  return mDbHandlePtr ? *mDbHandlePtr : 0;
}
}