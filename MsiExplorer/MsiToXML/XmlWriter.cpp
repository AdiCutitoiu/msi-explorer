#include "stdafx.h"
#include "XmlWriter.h"
#include "TableWriter.h"

XmlWriter::XmlWriter(std::wostream & aOstream, const wstring & aMsiPath)
  : Writer(aOstream)
  , kDatabase(aMsiPath)
{
}

void XmlWriter::Write() const
{
  mOstream << L"<Database>\n";

  auto tableNames = kDatabase.GetTableNames();

  for (const auto & name : tableNames)
  {
    TableWriter tableWriter(mOstream, kDatabase.GetTable(name));

    tableWriter.Write();
  }

  mOstream << L"</Database>\n";
}