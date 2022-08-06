#include <ray_caster.h>
#include <glad/glad.h>
#include <iostream>

using namespace Core;

Line::~Line()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

RayCaster::RayCaster(int width, int height)
{
  m_Width = width;
  m_Height = height;
}

RayCaster::~RayCaster()
{
}

void RayCaster::Cast(glm::vec2 origin, glm::vec2 direction)
{
  Cast({ origin, direction });
}

void RayCaster::Clear()
{
  for (auto line : m_Lines)
  {
    delete line;
  }
  m_Lines.clear();
}

void RayCaster::Cast(Ray ray)
{
  glm::vec2 current = ray.origin;
  glm::vec2 direction = ray.direction;

  // as of now, the cast is made by incrementing the origin by the direction
  // until the origin is outside of the screen. It works, but is certainly not the
  // best way to do this. The proper way is to find the straight line equation, it would
  // also be useful to detect collisions and be more precise. TODO: Find line equation
  while (current.x < m_Width && current.y < m_Height && current.x > 0 && current.y > 0)
  {
    current += direction;
  }
  current -= direction;

  Line *line = new Line();
  line->start = ray.origin;
  line->end = current;
  line->color = glm::vec3(1.0f, 1.0f, 1.0f);
  line->data[0] = line->start.x;
  line->data[1] = line->start.y;
  line->data[2] = line->end.x;
  line->data[3] = line->end.y;

  glGenVertexArrays(1, &line->VAO);
  glGenBuffers(1, &line->VBO);
  glBindVertexArray(line->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, line->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(line->data) * 4, &line->data[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_Lines.push_back(line);
}

void RayCaster::Draw(Shader *shader)
{
  shader->Use();
  for (auto& line : m_Lines)
  {
    shader->SetVector3f("color", line->color);
    glBindVertexArray(line->VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
  }
}