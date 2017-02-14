#include "stdafx.h"
#include "TableWriter.h"

TableWriter::TableWriter(std::wostream & aOstream, const MsInstallerTable & aTable)
  : Writer(aOstream)
  , mTable(aTable)
{
}

void TableWriter::Write() const
{
  mOstream << L"\t" << L"<Table Name=\"" << mTable.GetName() << "\">\n";

  auto schema = mTable.GetTableSchema();
  TableSchemaWriter schemaWriter(mOstream, schema);
  schemaWriter.Write();

  TableContentWriter contentWriter(mOstream, mTable);
  contentWriter.Write();

  mOstream << L"\t" << L"</Table>\n";
}
