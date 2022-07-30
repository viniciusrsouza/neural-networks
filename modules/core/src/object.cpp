#include <object.h>
#include <iostream>

using namespace Core;

Object::Object(Shape *shape, glm::vec2 position, glm::vec2 scale, float rotation)
{
  m_Shape = shape;
  m_Position = position;
  m_Scale = scale;
  m_Rotation = rotation;
}

Object::Object(Shape *shape): Object(shape, glm::vec2(0.0f), glm::vec2(1.0f), 0.0f)
{
}

Object::~Object()
{
}

glm::vec2 Object::GetPosition() const
{
  return glm::vec2(m_Position);
}

glm::vec2 Object::GetScale() const
{
  return glm::vec2(m_Scale);
}

void Object::Bind()
{
  // m_Shape->Bind();
}

void Object::Draw(Shader *shader) const
{
  if (shader)
  {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_Position, 0.0f));
    model = glm::scale(model, glm::vec3(m_Scale, 1.0f));
    model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    shader->SetMatrix4("model", model);
  }
  m_Shape->Draw(shader);
}