#include <resource_manager.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Core;

ResourceManager::ResourceManager(): ResourceManager("./")
{
}

ResourceManager::ResourceManager(std::string prefix)
{
  m_prefix = prefix;
}

std::string ResourceManager::GetPath(std::string file) const
{
  return m_prefix + file;
}

std::string ResourceManager::ReadFile(std::string file) const
{
  std::ifstream stream(GetPath(file));
  if (!stream.is_open())
  {
    std::cout << "Failed to open file: " << file << std::endl;
    return nullptr;
  }
  std::stringstream buffer;
  buffer << stream.rdbuf();
  return buffer.str().c_str();
}