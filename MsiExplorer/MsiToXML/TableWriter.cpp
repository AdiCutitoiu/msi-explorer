#include "stdafx.h"
#include "TableWriter.h"

TableWriter::TableWriter(std::wostream & aOstream, const MsInstallerTable & aTable)
  : Writer(aOstream)
  , kTable(aTable)
{
}

void TableWriter::Write() const
{
  mOstream << L"\t" << L"<Table Name=\"" << kTable.GetName() << "\">\n";

  auto schema = kTable.GetTableSchema();
  TableSchemaWriter schemaWriter(mOstream, schema);
  schemaWriter.Write();

  TableContentWriter contentWriter(mOstream, kTable);
  contentWriter.Write();

  mOstream << L"\t" << L"</Table>\n";
}
