// MsiToXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../MsiFramework/MsInstallerDatabase.h"
#include "CmdHandler.h"
#include "XmlWriter.h"

int main(int argc, char *argv[])
{
  auto start = ::GetTickCount();

  try
  {
    CmdHandler cmd(argc, argv);

    auto path     = cmd.GetMsiPath();

    auto xmlPath = cmd.GetXmlPath();
    wofstream out(xmlPath);

    XmlWriter(out, path).Write();
  }
  catch (std::wstring & aMessage)
  {
    wcout << aMessage << L'\n';
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

  cout << "Time: " << double(::GetTickCount() - start) / 1000 << " seconds";

  return 0;
}
