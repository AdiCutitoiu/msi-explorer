#pragma once

class ColumnSelector
{
public:
  ColumnSelector(const std::vector<std::wstring> & aColumns = { L"*" });

  /**
   * @returns a string "SELECT Col1,Col2,Col3" where Col1, Col2, Col3 are components of mColumns
   */
  wstring Get() const;

  /**
   * @returns a vector consisting of all the column names in the table
   */
  vector<wstring> GetColumnNames() const;

private:
  std::vector<std::wstring> mColumns;
};
