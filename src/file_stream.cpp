#include <cstdint>
#include <filesystem>
#include <fstream>

#include <file_stream.hpp>

FileStream::FileStream(const std::filesystem::path& path, std::ios::openmode mode)
: m_Path(path),
  m_File(path, mode)
{
}

void FileStream::WriteData(const char* data, uint64_t size)
{
  m_File.write(data, size);
}

void FileStream::ReadData(char* data, uint64_t size)
{
  m_File.read(data, size);
}
