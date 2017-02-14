#pragma once
#include "Writer.h"
#include "../MsiFramework/MsInstallerTableSchema.h"

class TableSchemaWriter : public Writer
{
public:
  TableSchemaWriter(std::wostream & aOstream, const MsInstallerTableSchema & aSchema);

  void Write() const override;

private:
  void WriteColumnTag(const MsInstallerTableSchema::ColumnAttributes & aAttributes) const;

  const MsInstallerTableSchema kSchema;
};