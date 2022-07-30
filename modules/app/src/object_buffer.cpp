#include <object_buffer.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

float min(float a, float b)
{
  return a < b ? a : b;
}

float max(float a, float b)
{
  return a > b ? a : b;
}

ObjectBuffer::ObjectBuffer(int width, int height)
{
  m_Width = width;
  m_Height = height;
  m_Speed = 200.0f;
  m_GenerateTime = 0;
  m_GenerationSpeed = 1.0f;
  srand(time(NULL));
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
      glm::vec2(m_Width, rand() % m_Height),
      glm::vec2(20.0f, 20.0f),
      0.0f,
      m_Speed
    )
  );
}

void ObjectBuffer::Update(float dt, float ellapsedTime)
{
  if (ellapsedTime - m_GenerateTime > m_GenerationSpeed)
  {
    Generate();
    m_GenerateTime = ellapsedTime;
    m_GenerationSpeed = 1.0f / (ellapsedTime / 10.0f);
    m_GenerationSpeed = min(max(m_GenerationSpeed, 0.25f), 1.0f);
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