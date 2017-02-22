#include "stdafx.h"
#include "MsiXMLTreeBuilder.h"

unique_ptr<XMLNode> MsiXMLTreeBuilder::GetRoot(const MsInstallerDatabase & aDatabase) const
{
  return MakeDatabaseNode(aDatabase);
}

unique_ptr<XMLNode> MsiXMLTreeBuilder::MakeDatabaseNode(const MsInstallerDatabase & aDatabase) const
{
  auto node = XMLNode::MakeMultiline(L"Database");

  auto tableNames = aDatabase.GetTableNames();

  for (const auto name : tableNames)
  {
    auto table = aDatabase.GetTable(name);

    node->AddChild(MakeTableNode(table));
  }

  return node;
}

unique_ptr<XMLNode> MsiXMLTreeBuilder::MakeTableNode(const MsInstallerTable & aTable) const
{
  vector<XMLNode::Attribute> attributes = { { L"Name", aTable.GetName() } };

  auto node = XMLNode::MakeMultiline(L"Table", attributes);

  auto schema = aTable.GetTableSchema();
  node->AddChild(MakeSchemaNode(schema));

  node->AddChild(MakeContentNode(aTable));

  return node;
}

unique_ptr<XMLNode> MsiXMLTreeBuilder::MakeSchemaNode(const MsInstallerTableSchema & aSchema) const
{
  auto node = XMLNode::MakeMultiline(L"Schema");

  auto colAttributes = aSchema.GetColumnAttributes();

  for (const auto & attribute : colAttributes)
  {
    node->AddChild(MakeColumnNode(attribute));
  }

  return node;
}

unique_ptr<XMLNode> MsiXMLTreeBuilder::MakeColumnNode(const ColAttribute & aColumnAttribute) const
{
  using ID = MsInstallerTableSchema::ID;

  vector<XMLAttribute> attributes = {
    { L"Name", get<ID::ID_COLUMN_NAME>(aColumnAttribute) },
    { L"Type", get<ID::ID_COLUMN_TYPE>(aColumnAttribute) },
    { L"Nullable", (get<ID::ID_NULLABLE>(aColumnAttribute) ? L"T" : L"F") },
    { L"PrimaryKey", get<ID::ID_PRIMARY_KEY>(aColumnAttribute) ? L"T" : L"F" }
  };

  return XMLNode::MakeSingleLine(L"Column", attributes);
}

unique_ptr<XMLNode> MsiXMLTreeBuilder::MakeContentNode(const MsInstallerTable & aTable) const
{
  auto node = XMLNode::MakeMultiline(L"Content");

  auto view          = aTable.GetView();
  auto colAttributes = aTable.GetTableSchema().GetColumnAttributes();

  for (auto fetched = view.GetNext(); fetched.first; fetched = fetched = view.GetNext())
  {
    node->AddChild(MakeRowNode(fetched.second, colAttributes));
  }

  return node;
}

unique_ptr<XMLNode> MsiXMLTreeBuilder::MakeRowNode(
  const MsInstallerRecord & aRecord, const vector<ColAttribute> & aColumnsAttributes) const
{
  using ID = MsInstallerTableSchema::ID;

  vector<XMLAttribute> attributes(aRecord.GetFieldNumber());

  transform(aColumnsAttributes.begin(),
            aColumnsAttributes.end(),
            aRecord.cbegin(),
            attributes.begin(),
            [](const ColAttribute & aColAttribute, const MsInstallerCell & aCell) {
              return make_pair(get<ID::ID_COLUMN_NAME>(aColAttribute), aCell.Get());
            });

  attributes.erase(
    remove_if(attributes.begin(),
              attributes.end(),
              [](const XMLAttribute & aAttribute) { return aAttribute.second.empty(); }),
    attributes.end());

  return XMLNode::MakeSingleLine(L"Row", attributes);
}
