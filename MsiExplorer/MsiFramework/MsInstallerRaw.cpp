#include "stdafx.h"
#include "MsInstallerRaw.h"
#include "MsInstallerRawRecord.h"

MsInstallerRaw::MsInstallerRaw(MSIHANDLE aViewHandle, const vector<wstring> & aColumnNames)
{
  ::MsiViewFetch(aViewHandle, &aRawHandle);

  for (UINT fieldNumber = 0; fieldNumber <= aColumnNames.size(); ++fieldNumber)
    mRecords.push_back(MsInstallerRawRecord(aRawHandle, fieldNumber));
}
