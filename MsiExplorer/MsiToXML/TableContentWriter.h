#pragma once
#include "Writer.h"
#include "../MsiFramework/MsInstallerTable.h"
#include "../MsiFramework/MsInstallerRecord.h"

class TableContentWriter : public Writer
{
public:
  TableContentWriter(std::wostream & aOstream, const MsInstallerTable & aTable);

  void Write() const override;

private:
  void WriteRow(const MsInstallerRecord & aRow) const;

  MsInstallerTable mTable;
  vector<wstring>  mColumnNames;
};