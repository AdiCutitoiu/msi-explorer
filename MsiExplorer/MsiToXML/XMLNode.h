#pragma once

class XMLNode
{
public:
  using AttributeName  = wstring;
  using AttributeValue = wstring;
  using Attribute      = pair<AttributeName, AttributeValue>;

  static unique_ptr<XMLNode> MakeSingleLine(const AttributeName &   aName,
                                            const vector<Attribute> aAttributes = {});

  static unique_ptr<XMLNode> MakeMultiline(const AttributeName &   aName,
                                           const vector<Attribute> aAttributes = {});

  bool IsSingleLine() const;

  bool IsMultiline() const;

  bool AddChild(unique_ptr<XMLNode> aXMLNode);

  vector<const XMLNode *> GetChildren() const;

  bool HasChildren() const;

  vector<Attribute> GetAttributes() const;

  wstring GetName() const;

  ~XMLNode();

private:
  XMLNode(const AttributeName & aName, const vector<Attribute> aAttributes, bool aIsMultiline);

  vector<unique_ptr<XMLNode>> mChildren;
  wstring                     mName;
  vector<Attribute>           mAttributes;
  bool                        mIsMultiline;
};
