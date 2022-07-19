#pragma once

#include <shape.h>
#include <shader.h>

namespace Core
{
  class Triangle : public Shape
  {
  public:
    Triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c);
    // Triangle(const Triangle &triangle);
    ~Triangle();
    
    virtual void Bind();
    virtual void Draw(Shader *shader = nullptr) const;
    
  private:
    glm::vec2 m_a;
    glm::vec2 m_b;
    glm::vec2 m_c;

    float m_vertices[6];
    unsigned int m_VBO, m_VAO;
  };
}

namespace Primitives
{
  static Core::Triangle EQ_TRIANGLE(
    glm::vec2(-1.0f, -1.0f), 
    glm::vec2(1.0f, -1.0f), 
    glm::vec2(0.0f, 1.0f)
  );
}