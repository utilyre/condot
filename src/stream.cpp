#include <type_traits>
#include <cstdint>
#include <string>

#include <stream.hpp>

bool StreamWriter::WriteString(const std::string& s)
{
  if (!WriteRaw((uint64_t)s.size()))
  {
    return false;
  }

  return WriteData(s.data(), s.size() * sizeof(char));
}

template<typename T>
bool StreamWriter::WriteVector(const std::vector<T>& v)
{
  if (!WriteRaw((uint64_t)v.size()))
  {
    return false;
  }

  if constexpr (std::is_trivial<T>())
  {
    return WriteData(&v[0], v.size());
  }

  for (const T& x : v)
  {
    if (!WriteObject(v))
    {
      return false;
    }
  }
}

bool StreamReader::ReadString(std::string& s)
{
  uint64_t size;
  if (!ReadRaw(size))
  {
    return false;
  }

  s.resize(size);
  return ReadData(s.data(), s.size());
}

template<typename T>
bool StreamReader::ReadVector(std::vector<T>& v)
{
  uint64_t size;
  if (!ReadRaw(size))
  {
    return false;
  }

  v.resize(size);

  if constexpr (std::is_trivial<T>())
  {
    return ReadData(&v[0], v.size());
  }

  for (T& x : v)
  {
    if (!ReadObject(v))
    {
      return false;
    }
  }

  return v;
}
