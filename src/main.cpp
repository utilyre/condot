#include <file_stream.hpp>
#include <iostream>

struct Data {
  int age;
};

int main()
{
  FileStream f(
    "data.bin",
    std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary
  );
  if (!f) return 1;

  std::vector<int> arr;
  arr.push_back(1);
  arr.push_back(2);
  arr.push_back(3);

  f.WriteVector(arr);
}
