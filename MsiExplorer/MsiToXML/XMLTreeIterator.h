#pragma once
#include "XMLNode.h"

class XMLTreeIterator
{
public:
  XMLTreeIterator();

  XMLTreeIterator(const XMLNode * aRoot);

  XMLTreeIterator & operator++();

  XMLTreeIterator operator++(int);

  const XMLNode * operator->() const;

  bool operator!=(const XMLTreeIterator & aIterator) const;

  bool operator==(const XMLTreeIterator & aIterator) const;

private:
  void FindNext();

  const XMLNode * mRootNode;
  const XMLNode * mPrevNode;
  const XMLNode * mCurrentNode;
};
