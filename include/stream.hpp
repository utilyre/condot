#pragma once

#include <cstdint>
#include <string>
#include <vector>

class StreamWriter
{
public:
  virtual ~StreamWriter() {}

  virtual bool IsStreamGood() const = 0;
  virtual bool WriteData(const char* data, uint64_t size) = 0;

  operator bool() const { return IsStreamGood(); }

  template<typename T>
  bool WriteRaw(const T&  v) { return WriteData((const char*)&v, sizeof(T)); }

  template<typename T>
  bool WriteObject(const T& v) { return T::Serialize(*this, v); }

  bool WriteString(const std::string& s);

  template<typename T>
  bool WriteVector(const std::vector<T>& v);
};

class StreamReader
{
public:
  virtual ~StreamReader() {}

  virtual bool IsStreamGood() const = 0;
  virtual bool ReadData(char* data, uint64_t size) = 0;

  operator bool() const { return IsStreamGood(); }

  template<typename T>
  bool ReadRaw(T&  v) { return ReadData((char*)&v, sizeof(T)); }

  template<typename T>
  bool ReadObject(T& v) { return T::Deserialize(*this, v); }

  bool ReadString(std::string& s);

  template<typename T>
  bool ReadVector(std::vector<T>& v);
};
