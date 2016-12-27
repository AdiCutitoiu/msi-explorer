#include "stdafx.h"
#include "RecordFieldStringGetter.h"

std::wstring RecordFieldStringGetter::Get(MSIHANDLE aRecord, int aField)
{
  DWORD buffSize = 0;
  ::MsiRecordGetString(aRecord, aField, L"", &buffSize);

  ++buffSize;
  wstring result(buffSize, ' ');
  ::MsiRecordGetString(aRecord, aField, &result[0], &buffSize);
  result.pop_back();

  return result;
}
