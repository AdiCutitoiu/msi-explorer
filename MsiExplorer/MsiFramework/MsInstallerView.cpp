#include "stdafx.h"
#include "MsInstallerView.h"
#include "RecordFieldStringGetter.h"

MsInstallerView::MsInstallerView(MSIHANDLE               aDatabaseHandle,
                                 const wstring &         aTableName,
                                 const vector<wstring> & aTableColumns /*= { L"" }*/)
  : mViewHandle(0)
  , mCurrentRecordHandle(0)
  , mState(State::UNINITIALIZED)
{
  wstring columns = accumulate(aTableColumns.begin(), aTableColumns.end(), wstring(),
                               [](const wstring & aResult, const wstring & aColumnName) {
                                 return aResult == L"" ? aColumnName : aResult + L"," + aColumnName;
                               });

  wstring query = L"SELECT " + columns + L" FROM " + aTableName;

  ::MsiDatabaseOpenView(aDatabaseHandle, query.c_str(), &mViewHandle);
}

void MsInstallerView::Execute()
{
  if (mState == State::FINISHED)
  {
    ::MsiViewClose(mViewHandle);
  }

  if (mState == State::FINISHED || mState == State::UNINITIALIZED)
  {
    MSIHANDLE record = 0;
    ::MsiViewExecute(mViewHandle, record);
  }

  mState = State::NOT_FINISHED;
}

bool MsInstallerView::UpdateCurrent(const MsInstallerRecord & aRecord)
{
  MsInstallerRecord backup(mCurrentRecordHandle);

  UpdateCurrentHandle(aRecord);

  if (::MsiViewModify(mViewHandle, MSIMODIFY_UPDATE, mCurrentRecordHandle) != ERROR_SUCCESS)
  {
    UpdateCurrentHandle(backup);
    return false;
  }

  return true;
}

pair<bool, MsInstallerRecord> MsInstallerView::GetNext()
{
  if (mCurrentRecordHandle != 0)
  {
    MsiCloseHandle(mCurrentRecordHandle);
  }

  if (::MsiViewFetch(mViewHandle, &mCurrentRecordHandle) == ERROR_SUCCESS)
  {
    int             fieldSize = ::MsiRecordGetFieldCount(mCurrentRecordHandle);
    vector<wstring> cellValues;

    for (int i = 1; i <= fieldSize; ++i)
    {
      cellValues.push_back(RecordFieldStringGetter::Get(mCurrentRecordHandle, i));
    }

    return make_pair(true, MsInstallerRecord(cellValues));
  }

  mState               = State::FINISHED;
  mCurrentRecordHandle = 0;

  return make_pair(false, MsInstallerRecord());
}

void MsInstallerView::UpdateCurrentHandle(const MsInstallerRecord & aRecord)
{
  int fieldSize = ::MsiRecordGetFieldCount(mCurrentRecordHandle);
  assert(fieldSize == aRecord.GetFieldNumber() && "Field sizes do not match");

  for (int field = 1; field <= fieldSize; ++field)
  {
    wstring replacement = aRecord.GetField(field).Get();

    ::MsiRecordSetString(mCurrentRecordHandle, field, replacement.c_str());
  }
}
