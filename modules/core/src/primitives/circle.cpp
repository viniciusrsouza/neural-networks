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

float Circle::GetRadius() const
{
  return m_Radius;
}

glm::vec2 Circle::GetCenter() const
{
  return m_Center;
}

/**
 * circle
 * (x - h)^2 + (y - k)^2 = r^2
 * x^2 - 2xh + h^2 + y^2 - 2yk + k^2 = r^2
 * 
 * line
 * y = m(x - x1) + y1
 * y = mx - mx1 + y1
 * c = - mx1 + y1
 * y = mx + c
 * 
 * w = c - k
 * 
 * (x - h)^2 + (mx + c - k)^2 = r^2
 * x^2 - 2xh + h^2 + (mx + w)^2 = r^2
 * x^2 - 2xh + h^2 + m^2x^2 + 2mxw + w^2 = r^2
 * (1 + m^2)x^2 + (2h + 2mw)x + (h^2 + w^2 - r^2) = 0
 * 
 * a = 1 + m^2
 * b = 2h + 2mw
 * c = h^2 + w^2 - r^2
 */

// check if line that passes through (x1, y1) and (x2, y2) intersects with circle (x, y, r)
bool Circle::Intersects(glm::vec2 p, glm::vec2 p1, glm::vec2 p2, glm::mat4 ortho) const
{ 
  float h = p.x, k = p.y, x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
  float r = m_Radius;
  glm::vec4 rv = glm::inverse(ortho) * glm::vec4(0, r, 0, 0);
  r = glm::abs(rv.y);

  float m = (y2 - y1) / (x2 - x1);
  float n = (-m * x1) + y1;
  float w = n - k;

  if (x1 == x2) {
    std::cout << "x1 == x2" << std::endl;
    std::cout << "x1: " << x1 << std::endl;
    std::cout << "h: " << h << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "h - r <= x1 && x1 <= h + r" << std::endl;
    std::cout << h << " - " << r << " <= " << x1 << " && " << x1 << " <= " << h << " + " << r << std::endl;
    std::cout << h - r << " <= " << x1 << " && " << x1 << " <= " << h + r << std::endl;
    std::cout << "x1 - r <= h && h <= x1 + r" << std::endl;
    if (h - r <= x1 && x1 <= h + r) {
      std::cout << "x1 is in circle" << std::endl;
      return true;
    }
    return false;
  }

  float a = 1 + m * m;
  float b = (2 * h) + (2 * m * w);
  float c = (h * h) + (w * w) - (r * r);
  float d = (b * b) - (4 * a * c);

  // std::cout << "p: " << p.x << ", " << p.y << std::endl;
  // std::cout << "p1: " << p1.x << ", " << p1.y << std::endl;
  // std::cout << "p2: " << p2.x << ", " << p2.y << std::endl;
  
  // std::cout << "a: " << a << std::endl;
  // std::cout << "b: " << b << std::endl;
  // std::cout << "c: " << c << std::endl;
  // std::cout << "d: " << d << std::endl;

  if (d < 0)
    return false;
  else if (d == 0)
    return true;
  else
    return true;
}