#pragma once

#include <cstdint>
#include <type_traits>
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

  bool WriteString(const std::string& s)
  {
    if (!WriteRaw((uint64_t)s.size()))
    {
      return false;
    }

    return WriteData(s.data(), s.size() * sizeof(char));
  }

  template<typename T>
  bool WriteVector(const std::vector<T>& v)
  {
    if (!WriteRaw((uint64_t)v.size()))
    {
      return false;
    }

    if constexpr (std::is_trivial<T>())
    {
      return WriteData((const char*)&v[0], v.size() * sizeof(T));
    }
    else
    {
      for (const T& x : v)
      {
        if (!WriteObject(x))
        {
          return false;
        }
      }

      return true;
    }
  }
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

  bool ReadString(std::string& s)
  {
    uint64_t size;
    if (!ReadRaw(size))
    {
      return false;
    }

    s.resize(size);
    return ReadData(s.data(), s.size() * sizeof(char));
  }

  template<typename T>
  bool ReadVector(std::vector<T>& v)
  {
    uint64_t size;
    if (!ReadRaw(size))
    {
      return false;
    }

    v.resize(size);

    if constexpr (std::is_trivial<T>())
    {
      return ReadData((char*)&v[0], v.size() * sizeof(T));
    }
    else
    {
      for (T& x : v)
      {
        if (!ReadObject(x))
        {
          return false;
        }
      }

      return true;
    }
  }
};
