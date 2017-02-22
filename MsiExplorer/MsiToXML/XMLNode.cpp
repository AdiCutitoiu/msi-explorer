#include "stdafx.h"
#include "XMLNode.h"

unique_ptr<XMLNode> XMLNode::MakeSingleLine(const AttributeName &   aName,
                                            const vector<Attribute> aAttributes /*= {}*/)
{
  return unique_ptr<XMLNode>(new XMLNode(aName, aAttributes, false));
}

unique_ptr<XMLNode> XMLNode::MakeMultiline(const AttributeName &   aName,
                                           const vector<Attribute> aAttributes /*= {}*/)
{
  return unique_ptr<XMLNode>(new XMLNode(aName, aAttributes, true));
}

bool XMLNode::IsSingleLine() const
{
  return !mIsMultiline;
}

bool XMLNode::IsMultiline() const
{
  return mIsMultiline;
}

bool XMLNode::AddChild(unique_ptr<XMLNode> aXMLNode)
{
  if (this->IsSingleLine())
    return false;

  mChildren.push_back(std::move(aXMLNode));
  return true;
}

vector<const XMLNode *> XMLNode::GetChildren() const
{
  vector<const XMLNode *> children(mChildren.size());

  std::transform(mChildren.begin(),
                 mChildren.end(),
                 children.begin(),
                 [](const unique_ptr<XMLNode> & aChild) { return aChild.get(); });

  return children;
}

bool XMLNode::HasChildren() const
{
  return !mChildren.empty();
}

vector<XMLNode::Attribute> XMLNode::GetAttributes() const
{
  return mAttributes;
}

wstring XMLNode::GetName() const
{
  return mName;
}

XMLNode::~XMLNode()
{
  deque<unique_ptr<XMLNode>> toDelete;
  move(mChildren.begin(), mChildren.end(), back_inserter(toDelete));
  mChildren.clear();

  while (!toDelete.empty())
  {
    auto toPop = toDelete.front().get();

    if (!toPop)
      int x = 2;

    auto & addedChildren = toPop->mChildren;
    move(addedChildren.begin(), addedChildren.end(), back_inserter(toDelete));
    addedChildren.clear();

    toDelete.pop_front();
  }
}

XMLNode::XMLNode(const AttributeName &   aName,
                 const vector<Attribute> aAttributes,
                 bool                    aIsMultiline)
  : mName(aName)
  , mAttributes(aAttributes)
  , mIsMultiline(aIsMultiline)
{
}
