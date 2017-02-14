#pragma once


class CmdHandler
{
public:
  /**
   * @brief Constructs a handler with the path to the msi
   */
  CmdHandler(int aArgCount, char *aArgArray[]);

  /**
   * @returns the path to the msi
   */
  wstring GetMsiPath();

  /**
   * @returns the parent folder of the msi
   */
  wstring GetParentFolderPath();

  /**
   * @return true if mMsiPath is a valid path to an msi
   */
  bool IsValidPath();

private:
  wstring mMsiPath; // the path to the msi
};