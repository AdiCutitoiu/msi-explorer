#pragma once
#include "Writer.h"
#include "../MsiFramework/MsInstallerDatabase.h"

class XmlWriter : public Writer
{
public:
  XmlWriter(std::wostream & aOstream, const wstring & aMsiPath);

  void Write() const override;

private:
  const MsInstallerDatabase kDatabase;
};