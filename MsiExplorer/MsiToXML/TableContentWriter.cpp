#include "stdafx.h"
#include "TableContentWriter.h"
#include "CharacterEscaper.h"

TableContentWriter::TableContentWriter(std::wostream & aOstream, const MsInstallerTable & aTable)
  : Writer(aOstream)
  , kTable(aTable)
  , mColumnNames(aTable.GetColumnNames())
{
}

void TableContentWriter::Write() const
{
  mOstream << L"\t\t" << L"<Content>\n";

  auto view = kTable.GetView();
  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    WriteRow(fetched.second);
  }

  mOstream << L"\t\t" << L"</Content>\n";
}

void TableContentWriter::WriteRow(const MsInstallerRecord & aRow) const
{
  using namespace SeqEscape;

  mOstream << L"\t\t\t" << L"<Row";

  // puts two string together separated by a space
  auto addStrings = [](const wstring & aResult, const wstring & aTagData) {
    return aResult + L" " + aTagData;
  };

  // concatenates name with value, Eg: Name="Dialog"
  auto concatValues = [](const wstring & aColName, const MsInstallerCell & aCell) {
    return aColName + L"=\"" + Escape(aCell.Get()) + L"\"";
  };

  // output all the tags
  mOstream << std::inner_product(
    mColumnNames.begin(), mColumnNames.end(), aRow.cbegin(), wstring(), addStrings, concatValues);

  mOstream << L"/>\n";
}
