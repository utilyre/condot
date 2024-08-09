#include <stream.hpp>

void StreamWriter::WriteZeros(uint64_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    WriteRaw('\0');
  }
}

void StreamWriter::WriteString(const std::string& s)
{
  WriteRaw((uint64_t)s.size());
  WriteData(s.data(), s.size() * sizeof(char));
}

void StreamReader::ReadString(std::string& s)
{
  uint64_t size;
  ReadRaw(size);

  s.resize(size);
  ReadData(s.data(), s.size() * sizeof(char));
}
