#include "stdafx.h"
#include "XMLTree.h"

XMLTree::XMLTree(unique_ptr<XMLNode> aRoot)
  : mRoot(move(aRoot))
{
}

XMLTreeIterator XMLTree::begin()
{
  return XMLTreeIterator(mRoot.get());
}

XMLTreeIterator XMLTree::end()
{
  return XMLTreeIterator();
}
