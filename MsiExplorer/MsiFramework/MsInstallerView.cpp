#include "stdafx.h"
#include "MsInstallerView.h"
#include "Predicate.h"
#include "RecordFieldStringGetter.h"

MsInstallerView::MsInstallerView(Utility::DatabaseHandle aDatabaseHandle,
                                 const wstring &         aTableName,
                                 const ColumnSelector &  aColumnSelector /*= ColumnSelector()*/,
                                 const Predicate &       aPredicate /*= Predicate()*/)
  : mDatabaseHandle(aDatabaseHandle)
  , mViewHandle(0)
  , mCurrentRecordHandle(0)
  , mState(State::UNINITIALIZED)
  , mColumnNames(aColumnSelector.GetColumnNames())
{
  wstring query = aColumnSelector.Get() + L" FROM " + aTableName;

  // add the condition only if it has any variables
  wstring predicateStr = aPredicate.Get();
  query += predicateStr.empty() ? L"" : L" " + predicateStr;

  auto st = ::MsiDatabaseOpenView(aDatabaseHandle, query.c_str(), &mViewHandle);
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

  UINT res;
  if ((res = ::MsiViewModify(mViewHandle, MSIMODIFY_UPDATE, mCurrentRecordHandle)) != ERROR_SUCCESS)
  {
    ERROR_FUNCTION_FAILED;

    PMSIHANDLE hLastErrorRec = MsiGetLastErrorRecord();

    TCHAR * szExtendedError  = NULL;
    DWORD   cchExtendedError = 0;
    if (hLastErrorRec)
    {
      // Since we are not currently calling MsiFormatRecord during an
      // install session, hInstall is NULL. If MsiFormatRecord was called
      // via a DLL custom action, the hInstall handle provided to the DLL
      // custom action entry point could be used to further resolve
      // properties that might be contained within the error record.

      // To determine the size of the buffer required for the text,
      // szResultBuf must be provided as an empty string with
      // *pcchResultBuf set to 0.

      UINT uiStatus = MsiFormatRecord(NULL, hLastErrorRec, TEXT(""), &cchExtendedError);

      if (ERROR_MORE_DATA == uiStatus)
      {
        // returned size does not include null terminator.
        cchExtendedError++;

        szExtendedError = new TCHAR[cchExtendedError];
        if (szExtendedError)
        {
          uiStatus = MsiFormatRecord(NULL, hLastErrorRec, szExtendedError, &cchExtendedError);
          if (ERROR_SUCCESS == uiStatus)
          {
            // We now have an extended error
            // message to report.

            // PLACE ADDITIONAL CODE HERE
            // TO LOG THE ERROR MESSAGE
            // IN szExtendedError.
          }

          delete[] szExtendedError;
          szExtendedError = NULL;
        }
      }
    }

    UpdateCurrentHandle(backup);
    return false;
  }

  return true;
}

bool MsInstallerView::Insert(const MsInstallerRecord & aRecord)
{
  // create a record
  UINT      fieldSize = ::MsiRecordGetFieldCount(mCurrentRecordHandle);
  MSIHANDLE newRecord = ::MsiCreateRecord(aRecord.GetFieldNumber());

  for (UINT field = 1; field <= aRecord.GetFieldNumber(); ++field)
  {
    wstring cellValue = aRecord.GetCell(field - 1).Get();
    ::MsiRecordSetString(newRecord, field, cellValue.c_str());
  }

  // insert the record
  UINT result = ::MsiViewModify(mViewHandle, MSIMODIFY_INSERT, newRecord);
  ::MsiViewModify(mViewHandle, MSIMODIFY_REFRESH, newRecord);

  return result == ERROR_SUCCESS;
}

bool MsInstallerView::InsertTemporary(const MsInstallerRecord & aRecord)
{
  // create a record
  UINT      fieldSize = ::MsiRecordGetFieldCount(mCurrentRecordHandle);
  MSIHANDLE newRecord = ::MsiCreateRecord(aRecord.GetFieldNumber());

  for (UINT field = 1; field <= aRecord.GetFieldNumber(); ++field)
  {
    wstring cellValue = aRecord.GetCell(field - 1).Get();
    ::MsiRecordSetString(newRecord, field, cellValue.c_str());
  }

  // insert the record
  UINT result = ::MsiViewModify(mViewHandle, MSIMODIFY_INSERT_TEMPORARY, newRecord);
  ::MsiViewModify(mViewHandle, MSIMODIFY_REFRESH, newRecord);

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

vector<wstring> MsInstallerView::GetColumnNames() const
{
  return mColumnNames;
}

bool MsInstallerView::DeleteCurrent()
{
  return MsiViewModify(mViewHandle, MSIMODIFY_DELETE, mCurrentRecordHandle) == ERROR_SUCCESS;
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
