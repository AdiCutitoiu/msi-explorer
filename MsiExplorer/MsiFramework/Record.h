#pragma once

class MsiRecord
{
public:
  // MsiRecord(MSIHANDLE aRecordhandle);
  //
  // vector<wstring> ToStringVector();
  //
  // UINT GetFieldNumber();
  //
  // wstring GetString(int aIndex);
  //
  // wstring SetString(int aIndex, const wstring & aString);

private:
  MSIHANDLE mRecordHandle;
};
