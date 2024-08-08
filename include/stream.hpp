#pragma once

#include <cstdint>
#include <type_traits>
#include <string>
#include <optional>
#include <vector>

class StreamWriter
{
public:
  virtual ~StreamWriter() {}

  virtual void WriteData(const char* data, uint64_t size) = 0;
  virtual bool IsStreamGood() const = 0;

  operator bool() const { return IsStreamGood(); }

  void WriteZeros(size_t size)
  {
    for (size_t i = 0; i < size; i++)
    {
      WriteRaw('\0');
    }
  }

  template<typename T>
  void WriteRaw(const T&  v) { WriteData((const char*)&v, sizeof(T)); }

  template<typename T>
  void WriteObject(const T& v) { T::Serialize(*this, v); }

  void WriteString(const std::string& s)
  {
    WriteRaw((uint64_t)s.size());
    WriteData(s.data(), s.size() * sizeof(char));
  }

  template<typename T>
  void WriteOptional(const std::optional<T>& o)
  {
    WriteRaw(o.has_value());

    if (!o.has_value())
    {
      WriteZeros(sizeof(T));
      return;
    }

    if constexpr (std::is_trivial<T>())
    {
      WriteRaw(o.value());
    }
    else
    {
      WriteObject(o.value());
    }
  }

  template<typename T>
  void WriteVector(const std::vector<T>& v, bool writeSize = true)
  {
    if (writeSize)
    {
      WriteRaw((uint64_t)v.size());
    }

    if constexpr (std::is_trivial<T>())
    {
      WriteData((const char*)&v[0], v.size() * sizeof(T));
    }
    else
    {
      for (const T& x : v)
      {
        WriteObject(x);
      }
    }
  }
};

class StreamReader
{
public:
  virtual ~StreamReader() {}

  virtual void ReadData(char* data, uint64_t size) = 0;
  virtual bool IsStreamGood() const = 0;

  operator bool() const { return IsStreamGood(); }

  template<typename T>
  void ReadRaw(T&  v) { ReadData((char*)&v, sizeof(T)); }

  template<typename T>
  void ReadObject(T& v) { T::Deserialize(*this, v); }

  void ReadString(std::string& s)
  {
    uint64_t size;
    ReadRaw(size);

    s.resize(size);
    ReadData(s.data(), s.size() * sizeof(char));
  }

  template<typename T>
  void ReadOptional(std::optional<T>& o)
  {
    bool hasValue;
    ReadRaw(hasValue);

    if (!hasValue)
    {
      o = std::nullopt;
      return;
    }

    T value;
    if constexpr (std::is_trivial<T>())
    {
      ReadRaw(value);
    }
    else
    {
      ReadObject(value);
    }
    o = value;
  }

  template<typename T>
  void ReadVectorInPlace(std::vector<T>& v)
  {
    if constexpr (std::is_trivial<T>())
    {
      ReadData((char*)&v[0], v.size() * sizeof(T));
    }
    else
    {
      for (T& x : v)
      {
        ReadObject(x);
      }
    }
  }

  template<typename T>
  void ReadVector(std::vector<T>& v)
  {
    uint64_t size;
    ReadRaw(size);

    v.resize(size);
    ReadVectorInPlace(v);
  }
};
