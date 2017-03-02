#include "stdafx.h"
#include "XMLTreeIterator.h"

XMLTreeIterator::XMLTreeIterator()
  : mRootNode(nullptr)
  , mPrevNode(nullptr)
  , mCurrentNode(nullptr)
{
}

XMLTreeIterator::XMLTreeIterator(const XMLNode * aRoot)
  : XMLTreeIterator()
{
  if (aRoot)
  {
    mRootNode = mCurrentNode = aRoot;
    mPrevNode                = aRoot->GetParent();
  }
}

XMLTreeIterator & XMLTreeIterator::operator++()
{
  // empty tree
  if (mCurrentNode == nullptr)
    return *this;

  if (mCurrentNode->GetParent() == mPrevNode || mCurrentNode->GetParent() == mPrevNode->GetParent())
  {
    if (mCurrentNode->HasChildren())
    {
      mPrevNode    = mCurrentNode;
      mCurrentNode = mCurrentNode->GetChild(0);
      return *this;
    }
  }

  FindNext();

  return *this;
}

XMLTreeIterator XMLTreeIterator::operator++(int)
{
  auto prevIter = *this;

  this->operator++();

  return prevIter;
}

const XMLNode * XMLTreeIterator::operator->() const
{
  return mCurrentNode;
}

bool XMLTreeIterator::operator!=(const XMLTreeIterator & aIterator) const
{
  return !this->operator==(aIterator);
}

bool XMLTreeIterator::operator==(const XMLTreeIterator & aIterator) const
{
  return mPrevNode == aIterator.mPrevNode && mCurrentNode == aIterator.mCurrentNode;
}

void XMLTreeIterator::FindNext()
{
  bool            hasSibling  = false;
  const XMLNode * nextSibling = nullptr;

  while (!hasSibling)
  {
    // visited all the nodes of the tree
    if (mCurrentNode == mRootNode)
    {
      *this = XMLTreeIterator();
      return;
    }

    // try to find the next sibling of this node
    auto siblings        = mCurrentNode->GetParent()->GetChildren();
    auto nextSiblingIter = find(siblings.begin(), siblings.end(), mCurrentNode) + 1;
    hasSibling           = nextSiblingIter != siblings.end();

    // save the sibling node
    if (nextSiblingIter != siblings.end())
      nextSibling = *nextSiblingIter;

    // go one level up in the tree
    mPrevNode    = mCurrentNode;
    mCurrentNode = mCurrentNode->GetParent();
  }

  // found sibling
  mCurrentNode = nextSibling;
}
