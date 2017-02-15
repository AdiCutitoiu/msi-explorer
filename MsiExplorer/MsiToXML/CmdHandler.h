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
   * @returns a path to an xml file in the same folder as the msi. The xml and msi files 
   * have the same name.
   */
  wstring GetXmlPath();


private:
  /**
   * @return true if mMsiPath is a valid path to an msi
   */
  static bool IsValidPath(const wstring & aMsiPath);


  wstring mMsiPath; // the path to the msi
};