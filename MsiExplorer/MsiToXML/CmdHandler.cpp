#include "stdafx.h"
#include "CmdHandler.h"

using namespace std;

CmdHandler::CmdHandler(int aArgCount, char * aArgArray[])
{
  assert(aArgCount > 1);

  // take the last path only
  char * str = aArgArray[aArgCount - 1];
  auto length = strlen(str);


  // store the path and transform all its characters into wide characters
  mMsiPath.resize(length, L' ');
  transform(str, str + length, mMsiPath.begin(), 
            [](char aChar) { return static_cast<wchar_t>(aChar); });

  if (!IsValidPath(mMsiPath))
    throw L"Invalid path: " + mMsiPath;
}

wstring CmdHandler::GetMsiPath()
{
  return mMsiPath;
}

wstring CmdHandler::GetParentFolderPath()
{
  auto last = mMsiPath.find_last_of(L'\\');

  return wstring(mMsiPath.begin(), mMsiPath.begin() + last + 1);
}

wstring CmdHandler::GetXmlPath()
{
  wstring path = mMsiPath;

  auto pos = path.find_last_of('.');

  path.replace(pos, 4, L".xml");

  return path;
}

bool CmdHandler::IsValidPath(const wstring & aMsiPath)
{
  // C:\Users\Folder1\Folder2\sample.msi
  static const wregex expression(L"^[A-Z]:\\\\([A-Za-z0-9 ]+\\\\)*[A-Za-z0-9 ]+\\.msi");

  return regex_match(aMsiPath, expression);
}
