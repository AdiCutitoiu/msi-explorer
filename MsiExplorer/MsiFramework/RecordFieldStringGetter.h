#pragma once

class RecordFieldStringGetter
{
public:
  static std::wstring Get(MSIHANDLE aRecord, int aField);
};