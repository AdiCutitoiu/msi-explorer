#pragma once

class XMLNode
{
public:
  using AttributeName  = wstring;                              // name of an attribute
  using AttributeValue = wstring;                              // value of an attribute
  using Attribute      = pair<AttributeName, AttributeValue>;  // an attribute

  /**
   * @brief Factory function for a single line Node
   *
   * @param aName the name of the node
   *
   * @param aAttributes the attributes of the node
   *
   * @returns a unique_ptr to the created node
   */
  static unique_ptr<XMLNode> MakeSingleLine(const AttributeName &   aName,
                                            const vector<Attribute> aAttributes = {});

  /**
   * @brief Factory function for a multiline Node
   *
   * @param aName the name of the node
   *
   * @param aAttributes the attributes of the node
   *
   * @returns a unique_ptr to the created node
   */
  static unique_ptr<XMLNode> MakeMultiline(const AttributeName &   aName,
                                           const vector<Attribute> aAttributes = {});

  /**
   * @returns true if this node is single line
   */
  bool IsSingleLine() const;

  /**
   * @returns true if this node is multi line
   */
  bool IsMultiline() const;

  /**
   * @brief adds a new child
   *
   * @param aXMLNode the new child of this node
   *
   * @returns true if the child was successfully added
   */
  bool AddChild(unique_ptr<XMLNode> aXMLNode);

  /**
   * @returns a vector of pointers to the children of this node
   */
  vector<const XMLNode *> GetChildren() const;

  /**
   * @returns the i-th child of this node or null ptr if the specified child does not exist
   *
   * @param aIndex the requested child
   *
   * @return a pointer to the requested child
   */
  const XMLNode * GetChild(UINT aIndex) const;

  /**
   * @returns a pointer to the parent of the node
   */
  const XMLNode * GetParent() const;

  /**
   * @returns true if this node has children
   */
  bool HasChildren() const;

  /**
   * @returns the number of children of this node
   */
  UINT GetChildCount() const;

  /**
   * @returns the attributes of this node
   */
  vector<Attribute> GetAttributes() const;

  /**
   * @returns the name of this node
   */
  wstring GetName() const;

  /**
   * @brief destructor of a node, uses iterative destruction
   */
  ~XMLNode();

private:
  /**
   * @param aName the name of the node
   *
   * @param aAttributes the attributes of the node
   *
   * @param aIsMultiline is true if the node is multiline
   */
  XMLNode(const AttributeName & aName, const vector<Attribute> & aAttributes, bool aIsMultiline);

  XMLNode *                   mParent;       // the parent of this node
  vector<unique_ptr<XMLNode>> mChildren;     // children of this node
  wstring                     mName;         // the name of the node
  vector<Attribute>           mAttributes;   // the attributes of the node
  bool                        mIsMultiline;  // is set to true if the node is multiline
};
