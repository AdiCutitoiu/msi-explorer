#pragma once
#include "../MsiFramework/MsInstallerDatabase.h"
#include "XMLNode.h"

class XmlWriter
{
public:
  /**
   * @param aXMLpath the path to the xml file to be written
   *
   * @param aUseTabs if true, indentation consists of tabs, if false of spaces
   */
  XmlWriter(const wstring & aXMLPath, bool aUseTabs);

  /**
   * @brief sets the path of the xml file
   *
   * @param aXMLPath the path to the xml file
   */
  void SetPath(const wstring & aXMLPath);

  /**
   * @brief Writes a tree of xml nodes with into mXMLPath file in xml format
   *
   * @param aRoot the root of the xml
   */
  void Write(const unique_ptr<XMLNode> & aRoot);

  /**
   * @brief switches to tab indentation
   */
  void EnableTabIndentation();

  /**
   * @brief switches to space indentation
   */
  void EnableSpaceIndentation();

private:
  // an element of the stack
  using stackElem = pair<const XMLNode *, char>;  // WARNING WITH BOOL

  // the state of a node
  enum : char  // WARNING WITH BOOL
  {
    NOT_PROCESSED = false,
    PROCESSED     = true
  };

  /**
   * @brief writes a multiline node in begin format: <Node At1="..." ...>
   *
   * @param aXMLNode the node to be written
   */
  void WriteBeginNode(const XMLNode * aXMLNode);

  /**
   * @brief writes a multiline node in begin format: </Node>
   *
   * @param aXMLNode the node to be written
   */
  void WriteEndNode(const XMLNode * aXMLNode);

  /**
   * @brief writes a single line node: <Node At1="..." At2="..." ... />
   *
   * @param aXMLNode the node to be written
   */
  void WriteSingleLineNode(const XMLNode * aXMLNode);

  /**
   * @brief increments the indentation with one tab or with 4 spaces
   */
  void IncrementIndentation();

  /**
   * @brief decrements the indentation with one tab or with 4 spaces
   */
  void DecrementIndentation();

  /**
   * @brief prints a line to the xml file, the line will be indented
   */
  void PrintLine(const wstring & aLine);

  /**
   * @brief updates the stack with the next nodes to visit
   */
  void UpdateStack();

  wstring          mXMLPath;      // path of the xml file
  wstring          mIndentation;  // indentation of the current node
  wofstream        mOfstream;     // the ostream where the lines will be flushed
  stack<stackElem> mStack;        // keeps track of the current node
  bool             mUseTabs;      // keeps track whether spaces or tabs are used
};
