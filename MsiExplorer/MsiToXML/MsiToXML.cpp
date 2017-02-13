// MsiToXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../MsiFramework/MsInstallerDatabase.h"
#include "CmdHandler.h"

int main(int argc, char *argv[])
{
  CmdHandler cmd(argc, argv);
  
  if (cmd.IsValidPath())
  {
    auto path = cmd.GetMsiPath();
    auto parent = cmd.GetParentFolderPath();
  }


  /*
  MsInstallerDatabase db(L"C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi");
  auto                table = db.GetTable(L"Dialog");
  auto schema = table.GetTableSchema();

  auto view = table.GetView();

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    std::wcout << fetched.second[0].Get() << L'\n';
  }

  std::wcout << endl;

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    std::wcout << fetched.second[0].Get() << L'\n';
  }
  */
  return 0;
}
