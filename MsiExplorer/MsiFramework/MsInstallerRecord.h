#pragma once

#include "MsInstallerCell.h"
#include "RecordFieldStringGetter.h"

class MsInstallerRecord
{
public:
  /**
   * Constructs an empty record
   */
  MsInstallerRecord() = default;

  /**
   * Constructs a record from given cell values
   *
   * @param aCellValues the values of the cells
   */
  MsInstallerRecord(const std::vector<std::wstring> aCellsValues);

  /**
   * Constructs a record from a handle to a record
   *
   * @param aRecordHandle the handle from which the cell values are extracted
   */
  MsInstallerRecord(MSIHANDLE aRecordHandle);

  /**
   * @returns a reference to a cell found at a given index
   */
  MsInstallerCell & operator[](int aIndex);

  /**
   * @returns a const reference to a cell found at a given index
   */
  const MsInstallerCell & operator[](int aIndex) const;

  /**
   * @returns the field number of the record(the number of cells)
   */
  UINT GetFieldNumber() const;

  MsInstallerCell GetCell(int aIndex) const;

  void SetCell(int aIndex, const MsInstallerCell & aCell);

  /**
   * @returns an iterator to the first cell in the record
   */
  std::vector<MsInstallerCell>::iterator begin();

  /**
   * @returns an end iterator
   */
  std::vector<MsInstallerCell>::iterator end();

  /**
   * @returns a const iterator to the beginning of the record
   */
  std::vector<MsInstallerCell>::const_iterator cbegin() const;

  /**
   * @returns a const iterator to the end of the record
   */
  std::vector<MsInstallerCell>::const_iterator cend() const;

private:
  std::vector<MsInstallerCell> mCells;  // the vector of cells
};
