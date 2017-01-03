#include "stdafx.h"
#include "RecordFieldStringGetter.h"

std::wstring RecordFieldStringGetter::Get(MSIHANDLE aRecord, int aField)
{
  DWORD buffSize = 0;
  UINT  res      = ::MsiRecordGetString(aRecord, aField, L"", &buffSize);
  ++buffSize;
  wstring result(buffSize, ' ');
  res = ::MsiRecordGetString(aRecord, aField, &result[0], &buffSize);
  result.pop_back();

  return result;
}
