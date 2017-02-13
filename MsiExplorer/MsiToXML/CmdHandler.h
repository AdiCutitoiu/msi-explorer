#pragma once


class CmdHandler
{
public:
  CmdHandler(int aArgc, char *aArgv[]);

  wstring GetMsiPath();

  wstring GetParentFolderPath();

  bool IsValidPath();
private:

  wstring mMsiPath;
};