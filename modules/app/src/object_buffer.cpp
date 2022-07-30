#include <object_buffer.h>
#include <iostream>

ObjectBuffer::ObjectBuffer(int width, int height)
{
  m_Width = width;
  m_Height = height;
  m_Speed = 200.0f;
  m_GenerateTime = 0;
}

ObjectBuffer::~ObjectBuffer()
{
  for (auto object : m_Objects)
  {
    delete object;
  }
}

void ObjectBuffer::Generate()
{
  m_Objects.push_back(
    new GeneratedObject(
      &Core::Primitives::SQUARE,
      glm::vec2(m_Width, m_Height / 2.0f),
      glm::vec2(20.0f, 20.0f),
      0.0f,
      m_Speed
    )
  );
}

void ObjectBuffer::Update(float dt, float ellapsedTime)
{
  int _ellapsedTime = (int)ellapsedTime;
  if ((_ellapsedTime % 3) == 0.0f && _ellapsedTime != m_GenerateTime)
  {
    Generate();
    m_GenerateTime = (int) ellapsedTime;
  }

  for (auto object : m_Objects)
  {
    object->Update(dt);
    if (object->GetPosition().x < 0 - object->GetScale().x)
    {
      m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
      delete object;
    }
  }
}

void ObjectBuffer::Render(Core::Shader *shader)
{
  for (auto object : m_Objects)
  {
    object->Draw(shader);
  }
}