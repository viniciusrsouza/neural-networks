#pragma once
#include <shape.h>
#include <shader.h>

namespace Core
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d);
    // ~Rectangle();

    virtual void Bind();
    virtual void Draw(Shader *shader = nullptr) const;
  
  private:
    glm::vec2 m_a;
    glm::vec2 m_b;
    glm::vec2 m_c;
    glm::vec2 m_d;

    float m_vertices[12];
    unsigned int m_VBO, m_VAO;
  };
}