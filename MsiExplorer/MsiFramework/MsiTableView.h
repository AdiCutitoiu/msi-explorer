#pragma once
#include "Record.h"

class MsiTableView
{
  // MsiTableView(MSIHANDLE aViewHandle);
  //
  // bool Execute();
  //
  // pair<bool, MsiRecord> Fetch();
  //
  //~MsiTableView();  // msi view close

private:
  MSIHANDLE mView;
};
