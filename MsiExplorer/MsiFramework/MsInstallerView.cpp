#include "stdafx.h"
#include "MsInstallerView.h"
#include "RecordFieldStringGetter.h"

MsInstallerView::MsInstallerView(Utility::DatabaseHandle aDatabaseHandle,
                                 const wstring &         aTableName,
                                 const vector<wstring> & aTableColumns /*= { L"" }*/)
  : mDatabaseHandle(aDatabaseHandle)
  , mViewHandle(0)
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

  if (::MsiViewModify(mViewHandle, MSIMODIFY_ASSIGN, mCurrentRecordHandle) != ERROR_SUCCESS)
  {
    UpdateCurrentHandle(backup);
    return false;
  }

  return true;
}

bool MsInstallerView::Insert(const MsInstallerRecord & aRecord)
{
  // if there are no records fetched, fetch a record and set isFinished flag to true
  bool isFinished = false;
  if (mState == State::FINISHED || mState == State::UNINITIALIZED)
  {
    isFinished = true;
    GetNext();
  }

  // create a record
  UINT      fieldSize = ::MsiRecordGetFieldCount(mCurrentRecordHandle);
  MSIHANDLE newRecord = ::MsiCreateRecord(fieldSize);

  assert(aRecord.GetFieldNumber() == fieldSize);
  for (UINT field = 1; field <= fieldSize; ++field)
  {
    wstring cellValue = aRecord.GetCell(field - 1).Get();
    ::MsiRecordSetString(newRecord, field, cellValue.c_str());
  }

  // insert the record
  UINT result = ::MsiViewModify(mViewHandle, MSIMODIFY_INSERT, newRecord);
  ::MsiViewModify(mViewHandle, MSIMODIFY_REFRESH, newRecord);

  // if the flag was set to true, close the view
  if (isFinished)
  {
    ::MsiCloseHandle(mCurrentRecordHandle);
    ::MsiViewClose(mViewHandle);
    mState = State::FINISHED;
  }

  return result == ERROR_SUCCESS;
}

pair<bool, MsInstallerRecord> MsInstallerView::GetNext()
{
  if (mCurrentRecordHandle != 0)
  {
    MsiCloseHandle(mCurrentRecordHandle);
  }

  if (mState != State::NOT_FINISHED)
  {
    Execute();
  }

  if (::MsiViewFetch(mViewHandle, &mCurrentRecordHandle) == ERROR_SUCCESS)
  {
    UINT            fieldSize = ::MsiRecordGetFieldCount(mCurrentRecordHandle);
    vector<wstring> cellValues;

    for (UINT i = 1; i <= fieldSize; ++i)
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
    wstring replacement = aRecord.GetCell(field - 1).Get();

    ::MsiRecordSetString(mCurrentRecordHandle, field, replacement.c_str());
  }
}
