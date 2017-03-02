// MsiToXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../MsiFramework/AndExpression.h"
#include "../MsiFramework/MsInstallerDatabase.h"
#include "../MsiFramework/OrExpression.h"
#include "../MsiFramework/Predicate.h"
#include "../MsiFramework/VariableExpression.h"
#include "CmdHandler.h"
#include "MsiXMLTreeBuilder.h"
#include "XMLTreeIterator.h"
#include "XmlWriter.h"

int main(int argc, char * argv[])
{
  auto var1 = make_shared<VariableExpression>(L"Attributes", L"4", false);
  auto var2 = make_shared<VariableExpression>(L"Width", L"370", false);
  auto var3 = make_shared<VariableExpression>(L"Height", L"270", false);

  auto      andexpr = make_shared<AndExpression>(var1, var2, var3);
  Predicate exp(andexpr);

  auto cond = exp.Get();

  auto start = ::GetTickCount();

  try
  {
    CmdHandler cmd(argc, argv);
    auto       path    = cmd.GetMsiPath();
    auto       xmlPath = cmd.GetXmlPath();

    MsiXMLTreeBuilder treeBuilder;
    auto              tree = treeBuilder.GetTree(MsInstallerDatabase(path));

    wstring str;
    int     counter = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it)
    {
      str += 'a';
      counter++;
    }
    wcout << counter << endl;

    // XmlWriter writer(xmlPath, true);
    // writer.Write(root);
  }
  catch (std::wstring & aMessage)
  {
    wcout << aMessage << L'\n';
  }
  /*
    MsInstallerDatabase db(L"C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi");
    auto                table  = db.GetTable(L"Dialog");
    auto                schema = table.GetTableSchema();

    auto view = table.GetView({ L"*" }, exp);

    for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
    {
      std::wcout << fetched.second[0].Get() << L'\n';
    }

    std::wcout << endl;
    var1->SetValue(L"65539");

    view = table.GetView({ L"*" }, exp);
    for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
    {
      std::wcout << fetched.second[0].Get() << L'\n';
    }*/

  cout << "Time: " << double(::GetTickCount() - start) / 1000 << " seconds";
  return 0;
}
