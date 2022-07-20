#include <generated_object.h>

GeneratedObject::GeneratedObject(Core::Shape *shape, glm::vec2 position, glm::vec2 scale, float rotation, float speed): Object(shape, position, scale, rotation)
{
  m_Speed = speed;
}

GeneratedObject::~GeneratedObject()
{
}

void GeneratedObject::Update(float dt)
{
  m_Position.x -= m_Speed * dt;
}