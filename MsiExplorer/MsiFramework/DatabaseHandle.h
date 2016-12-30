#pragma once

namespace Utility
{
class DatabaseHandle
{
public:
  DatabaseHandle() = default;
  DatabaseHandle(MSIHANDLE aDatabaseHandle);

  operator MSIHANDLE() const;

private:
  std::shared_ptr<MSIHANDLE> mDbHandlePtr;
};
}