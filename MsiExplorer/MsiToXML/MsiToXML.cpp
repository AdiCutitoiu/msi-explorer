// MsiToXML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../MsiFramework/AndExpression.h"
#include "../MsiFramework/MsInstallerDatabase.h"
#include "../MsiFramework/NotExpression.h"
#include "../MsiFramework/OrExpression.h"
#include "../MsiFramework/Predicate.h"
#include "../MsiFramework/VariableExpression.h"
#include "CmdHandler.h"
#include "XmlWriter.h"

int main(int argc, char * argv[])
{
  auto var1 = make_shared<VariableExpression>(L"Attributes", L"1");
  auto var2 = make_shared<VariableExpression>(L"Width", L"370");

  vector<shared_ptr<Expression>> vec     = { var1, var2 };
  auto                           andexpr = make_shared<AndExpression>(vec);
  auto                           exp     = Predicate(andexpr);

  auto cond = exp.Get();

  auto start = ::GetTickCount();

  /*
  try
  {
    CmdHandler cmd(argc, argv);

    auto path = cmd.GetMsiPath();

    auto      xmlPath = cmd.GetXmlPath();
    wofstream out(xmlPath);

    XmlWriter(out, path).Write();
  }
  catch (std::wstring & aMessage)
  {
    wcout << aMessage << L'\n';
  }
  */

  MsInstallerDatabase db(L"C:\\Users\\Adi Cutitoiu\\Desktop\\sample.msi");
  auto                table  = db.GetTable(L"Dialog");
  auto                schema = table.GetTableSchema();

  auto view = table.GetView({ L"*" }, exp);

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    std::wcout << fetched.second[0].Get() << L'\n';
  }

  std::wcout << endl;

  for (auto fetched = view.GetNext(); fetched.first; fetched = view.GetNext())
  {
    std::wcout << fetched.second[0].Get() << L'\n';
  }

  cout << "Time: " << double(::GetTickCount() - start) / 1000 << " seconds";

  return 0;
}
