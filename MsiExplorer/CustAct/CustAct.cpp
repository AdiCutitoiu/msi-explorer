// CustAct.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

UINT WINAPI DoStuff(MSIHANDLE aSession)
{
  ::MessageBox(NULL, TEXT("I am a cust act message box"), TEXT("Cust Act"), MB_OK);

  return ERROR_SUCCESS;
}
