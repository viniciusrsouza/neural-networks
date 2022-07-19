#pragma once

#include <string>

namespace Core
{
  class ResourceManager
  {
  public:
    ResourceManager();
    ResourceManager(std::string prefix);

    std::string GetPath(std::string file) const;
    std::string ReadFile(std::string file) const;

  private:
    std::string m_prefix;
  };
}