#pragma once
#include "../MsiFramework/MsInstallerDatabase.h"
#include "XMLNode.h"
#include "XMLTree.h"

class MsiXMLTreeBuilder
{
public:
  /**
   * @brief Creates a tree of XMLNodes and returns a pointer to the root of the tree
   *
   * @param aDatabase the msi database
   */
  XMLTree GetTree(const MsInstallerDatabase & aDatabase) const;

private:
  using ColAttribute = MsInstallerTableSchema::ColumnAttributes;
  using XMLAttribute = XMLNode::Attribute;

  /**
   * @brief builds a tree where the root is a database node. The children of this node are table
   * nodes.
   *
   * @param aDatabase the msi database
   *
   * @returns the root of the tree
   */
  unique_ptr<XMLNode> MakeDatabaseNode(const MsInstallerDatabase & aDatabase) const;

  /**
   * @brief builds a tree(with a table as root) with two children: a schema child(information about
   * the columns) and a content child(the records in the table).
   *
   * @param aTable the table for which the node is created
   *
   * @returns the root of the tree
   */
  unique_ptr<XMLNode> MakeTableNode(const MsInstallerTable & aTable) const;

  /**
   * @brief builds a tree(with a table schema as root). The children of the root are nodes
   * containing columns.
   *
   * @brief aSchema the table schema
   *
   * @returns the root of the tree
   */
  unique_ptr<XMLNode> MakeSchemaNode(const MsInstallerTableSchema & aSchema) const;

  /**
   * @brief creates a single line column node.
   *
   * @param aColumnAttributes the attributes of a column
   *
   * @returns the node
   */
  unique_ptr<XMLNode> MakeColumnNode(const ColAttribute & aColumnAttributes) const;

  /**
   * @brief builds a tree(with content as root). The children of the root are nodes
   * containing table rows.
   *
   * @param aTable the table containing the row nodes
   *
   * @returns the root of the tree
   */
  unique_ptr<XMLNode> MakeContentNode(const MsInstallerTable & aTable) const;

  /**
   * @brief creates a single line row node
   *
   * @aRecord the record for which the node is created
   *
   * @aColumnAttributes the attributes for each column in the table containing the record
   *
   * @returns the node
   */
  unique_ptr<XMLNode> MakeRowNode(const MsInstallerRecord &    aRecord,
                                  const vector<ColAttribute> & aColumnsAttributes) const;
};
