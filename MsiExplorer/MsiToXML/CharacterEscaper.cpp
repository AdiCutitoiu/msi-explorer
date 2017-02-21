#include "stdafx.h"
#include "CharacterEscaper.h"

namespace
{
std::map<wchar_t, wstring> escapeMap{
  { L'&', L"amp" }, { L'\"', L"quot" }, { L'\'', L"apos" }, { L'<', L"lt" }, { L'>', L"gt" }
};
}

namespace SeqEscape
{
wstring Escape(const wstring & aString)
{
  wstring result;

  for (wchar_t character : aString)
  {
    // escape current character if it needs escaping
    auto found = escapeMap.find(character);
    if (found != escapeMap.end())
      result.append(L'&' + found->second + L';');
    else
      result.push_back(character);
  }

  return result;
}
}
