#include "stdafx.h"
#include "XmlWriter.h"
#include "CharacterEscaper.h"

XmlWriter::XmlWriter(const wstring & aXMLPath, bool aUseTabs)
  : mXMLPath(aXMLPath)
  , mUseTabs(aUseTabs)
{
}

void XmlWriter::SetPath(const wstring & aXMLPath)
{
  mXMLPath = aXMLPath;
}

void XmlWriter::Write(const unique_ptr<XMLNode> & aRoot)
{
  mOfstream.open(mXMLPath);

  mOfstream << L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

  WriteNode(aRoot.get());
  mStack.push(make_pair(aRoot.get(), 0));

  while (!mStack.empty())
  {
    // find the next unprocessed child of the node
    auto   currentNode = mStack.top().first;
    auto & childIndex  = mStack.top().second;

    // no unprocessed child, must close the current node tag
    if (childIndex == currentNode->GetChildCount())
    {
      WriteEndNode(currentNode);
      mStack.pop();
      continue;
    }

    // unprocessed child, write and push it to the stack
    auto toPushChild = currentNode->GetChild(childIndex++);
    WriteNode(toPushChild);
    mStack.push(make_pair(toPushChild, 0));
  }

  mOfstream.close();
}

void XmlWriter::EnableTabIndentation()
{
  mUseTabs = true;
}

void XmlWriter::EnableSpaceIndentation()
{
  mUseTabs = false;
}

void XmlWriter::WriteNode(const XMLNode * aXMLNode)
{
  using namespace SeqEscape;
  wstring tag = L'<' + aXMLNode->GetName();

  auto xmlAttributes = aXMLNode->GetAttributes();
  for (const auto & attribute : xmlAttributes)
  {
    tag += L" " + attribute.first + L"=\"" + Escape(attribute.second) + L'\"';
  }

  tag += aXMLNode->IsMultiline() ? L">" : L"/>";

  PrintLine(tag);

  if (aXMLNode->IsMultiline())
    IncrementIndentation();
}

void XmlWriter::WriteEndNode(const XMLNode * aXMLNode)
{
  if (aXMLNode->IsSingleLine())
    return;

  DecrementIndentation();

  wstring tag = L"</" + aXMLNode->GetName() + L">";

  PrintLine(tag);
}

void XmlWriter::WriteSingleLineNode(const XMLNode * aXMLNode)
{
  using namespace SeqEscape;
  wstring tag = L'<' + aXMLNode->GetName();

  auto xmlAttributes = aXMLNode->GetAttributes();
  for (const auto & attribute : xmlAttributes)
  {
    tag += L" " + attribute.first + L"=\"" + Escape(attribute.second) + L'\"';
  }
  tag += L"/>";

  PrintLine(tag);
}

void XmlWriter::IncrementIndentation()
{
  if (mUseTabs)
    mIndentation += L"\t";
  else
    mIndentation += L"    ";
}

void XmlWriter::DecrementIndentation()
{
  if (mUseTabs && mIndentation.empty())
    return;

  if ((!mUseTabs) && mIndentation.size() < 4)
    return;

  if (mUseTabs)
    mIndentation.pop_back();
  else
    mIndentation.erase(mIndentation.begin() + mIndentation.size() - 4, mIndentation.end());
}

void XmlWriter::PrintLine(const wstring & aLine)
{
  mOfstream << mIndentation << aLine << L'\n';
}

void XmlWriter::UpdateStack()
{
  static vector<unique_ptr<XMLNode>> endNodes;
  auto                               popped = mStack.top();
  mStack.pop();

  auto & currentNode = popped.first;
  if (currentNode->IsMultiline() && popped.second == NOT_PROCESSED)
  {
    auto name = currentNode->GetName();
    endNodes.push_back(XMLNode::MakeMultiline(name));

    mStack.push(make_pair(endNodes.back().get(), PROCESSED));

    auto children = currentNode->GetChildren();
    for_each(children.rbegin(), children.rend(), [&](const XMLNode * aChildNode) {
      mStack.push(make_pair(aChildNode, NOT_PROCESSED));
    });
  }
}
