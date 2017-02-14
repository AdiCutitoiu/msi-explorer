#pragma once
#include "../MsiFramework/MsInstallerTable.h"
#include "Writer.h"
#include "TableSchemaWriter.h"
#include "TableContentWriter.h"

class TableWriter : public Writer
{
public:
  TableWriter(std::wostream & aOstream, const MsInstallerTable & aTable);

  void Write() const override;

private:
  const MsInstallerTable kTable;
};