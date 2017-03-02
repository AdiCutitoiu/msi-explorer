#pragma once
#include "XMLNode.h"

class XMLTreeIterator
{
public:
  XMLTreeIterator();

  XMLTreeIterator(const XMLNode * aRoot);

  XMLTreeIterator & operator++();

  XMLTreeIterator operator++(int);

  const XMLNode * operator->();

  bool operator!=(const XMLTreeIterator & aIterator);

  bool operator==(const XMLTreeIterator & aIterator);

private:
  void FindNext();

  const XMLNode * mRootNode;
  const XMLNode * mPrevNode;
  const XMLNode * mCurrentNode;
};
