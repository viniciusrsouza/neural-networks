#include <object.h>

using namespace Core;

Object::Object(Shape *shape)
{
  m_shape = shape;
}

Object::~Object()
{
}

glm::vec3 Object::GetPosition() const
{
  return glm::vec3(m_position);
}