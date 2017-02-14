#pragma once

class Writer
{
public:
  Writer(std::wostream & aOstream);

  virtual void Write() const = 0;

protected:
  std::wostream & mOstream;
};