#include "stdafx.h"
#include "ColumnSelector.h"

ColumnSelector::ColumnSelector(const std::vector<std::wstring> & aColumns /*= { L"*" }*/)
  : mColumns(aColumns)
{
}

wstring ColumnSelector::Get() const
{
  return L"SELECT " + accumulate(mColumns.begin(),
                                 mColumns.end(),
                                 wstring(),
                                 [](const wstring & aResult, const wstring & aCurrent) {
                                   return aResult.empty() ? aCurrent : aResult + L',' + aCurrent;
                                 });
}

vector<wstring> ColumnSelector::GetColumnNames() const
{
  return mColumns;
}
