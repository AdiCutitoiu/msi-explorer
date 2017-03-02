#pragma once
#include "XMLNode.h"
#include "XMLTreeIterator.h"

class XMLTree
{
public:
  XMLTree(unique_ptr<XMLNode> aRoot);

  XMLTreeIterator begin();

  XMLTreeIterator end();

private:
  unique_ptr<XMLNode> mRoot;
};
