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
  mChildren.back()->mParent = this;
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

const XMLNode * XMLNode::GetChild(UINT aIndex) const
{
  return aIndex < mChildren.size() ? mChildren[aIndex].get() : nullptr;
}

const XMLNode * XMLNode::GetParent() const
{
  return mParent;
}

bool XMLNode::HasChildren() const
{
  return !mChildren.empty();
}

UINT XMLNode::GetChildCount() const
{
  return mChildren.size();
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
  if (mChildren.empty())
    return;

  deque<unique_ptr<XMLNode>> toDelete;
  move(mChildren.begin(), mChildren.end(), back_inserter(toDelete));
  mChildren.clear();

  while (!toDelete.empty())
  {
    auto toPop = toDelete.front().get();

    auto & toDeleteChildren = toPop->mChildren;
    move(toDeleteChildren.begin(), toDeleteChildren.end(), back_inserter(toDelete));
    toDeleteChildren.clear();

    toDelete.pop_front();
  }
}

XMLNode::XMLNode(const AttributeName &     aName,
                 const vector<Attribute> & aAttributes,
                 bool                      aIsMultiline)
  : mParent(nullptr)
  , mName(aName)
  , mAttributes(aAttributes)
  , mIsMultiline(aIsMultiline)
{
}
