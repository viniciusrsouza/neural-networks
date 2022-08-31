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

void RayCaster::Cast(glm::vec2 origin, glm::vec2 direction, std::vector<Core::Object*> objects, glm::mat4 ortho)
{
  Cast({ origin, direction }, objects, ortho);
}

void RayCaster::Clear()
{
  for (auto line : m_Lines)
  {
    delete line;
  }
  m_Lines.clear();
}

float line_x(glm::vec2 a, glm::vec2 b, float y)
{
  float m = (b.y - a.y) / (b.x - a.x);
  float x = ((y -  a.y) / m) + a.x;
  return x;
}

float line_y(glm::vec2 a, glm::vec2 b, float x)
{
  float m = (b.y - a.y) / (b.x - a.x);
  float y = (m * (x - a.x)) + a.y;
  return y;
}

void RayCaster::Cast(Ray ray, std::vector<Core::Object*> objects, glm::mat4 ortho)
{
  glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec2 current = ray.origin;
  glm::vec2 direction = ray.direction;

  float height = direction.y > 0 ? m_Height : 0;
  float width = direction.x > 0 ? m_Width : 0;

  // point that intersects height
  glm::vec2 p_height = glm::vec2(line_x(current, current + direction, height), height);
  
  // point that intersects width
  glm::vec2 p_width = glm::vec2(width, line_y(current, current + direction, width));

  glm::vec2 destiny = glm::length(p_height - current) < glm::length(p_width - current) ? p_height : p_width;

  bool some = false;
  for (auto object : objects)
  {
    bool intersects = object->GetShape()->Intersects(object->GetPosition(), current, current + direction, ortho);
    if (intersects)
    {
      some = true;
      color = glm::vec3(1.0f, 0.0f, 0.0f);
      // destiny = object->GetPosition();
    }
  }

  // std::cout << "some: " << some << std::endl;
  // if (m_Intersects)
  // {
  //   glm::vec2* collision = m_Intersects(current);
  //   if (collision && glm::length(*collision - current) < glm::length(destiny - current))
  //   {
  //     destiny = *collision;
  //   }
  // }

  Line *line = new Line();
  line->start = ray.origin;
  line->end = destiny;
  line->color = color;
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