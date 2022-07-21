#include <primitives/circle.h>
#include <glad/glad.h>
#include <iostream>

using namespace Core;

Circle::Circle(glm::vec2 center, float radius, float segments)
{
  m_Center = center;
  m_Radius = radius;
  m_Segments = segments;
  
  m_VBO = 0;
  m_VAO = 0;
  m_Vertices = std::vector<float>();

  m_Vertices.push_back(center.x); 
  m_Vertices.push_back(center.y);
  for (int i = 0; i < segments; i++)
  {
    float theta = 2.0f * 3.1415926f * float(i) / float(segments);
    float x = m_Radius * cosf(theta);
    float y = m_Radius * sinf(theta);
    m_Vertices.push_back(x + m_Center.x);
    m_Vertices.push_back(y + m_Center.y);
  }
  m_Vertices.push_back(m_Vertices[2]);
  m_Vertices.push_back(m_Vertices[3]);
}

void Circle::Bind()
{
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindVertexArray(m_VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), &m_Vertices[0], GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Circle::Draw(Shader *shader) const
{
  if (shader)
    shader->Use();
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLE_FAN, 0, m_Vertices.size() / 2);
  glBindVertexArray(0);
}