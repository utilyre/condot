#pragma once

#include <string>

class Card
{
public:
  Card(const std::string& name);

  const std::string& GetName() const;

private:
  std::string m_Name;
};
