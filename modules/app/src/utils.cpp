#include <utils.h>

float Utils::Min(float a, float b)
{
  return a < b ? a : b;
}

float Utils::Max(float a, float b)
{
  return a > b ? a : b;
}

bool Utils::Collides(Core::Circle a, Core::Circle b)
{
  return glm::distance(a.GetCenter(), b.GetCenter()) < a.GetRadius() + b.GetRadius();
}