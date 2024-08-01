#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>

#include <stream.hpp>

class FileStream : public StreamWriter, public StreamReader
{
public:
  explicit FileStream(
    const std::filesystem::path& path,
    std::ios::openmode mode = std::ios::out | std::ios::in | std::ios::binary
  );
  FileStream(const FileStream&) = delete;

  operator bool() const { return IsStreamGood(); }

  bool IsStreamGood() const override { return m_File.good(); }
  bool WriteData(const char* data, uint64_t size) override;
  bool ReadData(char* data, uint64_t size) override;

private:
  std::filesystem::path m_Path;
  std::fstream m_File;
};
