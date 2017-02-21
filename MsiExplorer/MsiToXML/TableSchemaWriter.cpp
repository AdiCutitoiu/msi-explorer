#include "stdafx.h"
#include "TableSchemaWriter.h"
#include "CharacterEscaper.h"

TableSchemaWriter::TableSchemaWriter(std::wostream &                aOstream,
                                     const MsInstallerTableSchema & aSchema)
  : Writer(aOstream)
  , kSchema(aSchema)
{
}

void TableSchemaWriter::Write() const
{
  mOstream << L"\t\t<Schema>\n";

  auto columnAttributes = kSchema.GetColumnAttributes();
  for (const auto & attributes : columnAttributes)
  {
    WriteColumnTag(attributes);
  }

  mOstream << L"\t\t</Schema>\n";
}

void TableSchemaWriter::WriteColumnTag(
  const MsInstallerTableSchema::ColumnAttributes & aAttributes) const
{
  using namespace SeqEscape;
  using ID = MsInstallerTableSchema::ID;

  mOstream << L"\t\t\t";

  mOstream << L"<Column ";

  mOstream << L"Name=\"" << Escape(get<ID::ID_COLUMN_NAME>(aAttributes)) << L"\" ";

  mOstream << L"Type=\"" << Escape(get<ID::ID_COLUMN_TYPE>(aAttributes)) << L"\" ";

  mOstream << L"Nullable=\"" << (get<ID::ID_NULLABLE>(aAttributes) ? "T" : "F") << L"\" ";

  mOstream << L"PrimaryKey=\"" << (get<ID::ID_PRIMARY_KEY>(aAttributes) ? L"T" : L"F") << L"\"";

  mOstream << L"/>\n";
}
