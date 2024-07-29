#include <cstdint>
#include <filesystem>
#include <fstream>

#include <file_stream.hpp>

FileStream::FileStream(const std::filesystem::path& path, std::ios::openmode mode)
: m_Path(path),
  m_File(path, mode)
{
}

bool FileStream::WriteData(const char* data, uint64_t size)
{
  m_File.write(data, size);
  return m_File.good();
}

bool FileStream::ReadData(char* data, uint64_t size)
{
  m_File.read(data, size);
  return m_File.good();
}
