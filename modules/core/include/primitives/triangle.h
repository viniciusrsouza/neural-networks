#pragma once

#include <shape.h>
#include <shader.h>

namespace Core
{
  class Triangle : public Shape
  {
  public:
    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    // Triangle(const Triangle &triangle);
    ~Triangle();
    
    virtual void Bind();
    virtual void Draw(Shader *shader = nullptr) const;
    
  private:
    glm::vec3 m_a;
    glm::vec3 m_b;
    glm::vec3 m_c;

    float m_vertices[9];
    unsigned int m_VBO, m_VAO;
  };
}

namespace Primitives
{
  static const Core::Triangle EQ_TRIANGLE(
    glm::vec3(-0.5f, -0.5f, 0.0f), 
    glm::vec3(0.5f, -0.5f, 0.0f), 
    glm::vec3(0.0f, 0.5f, 0.0f)
  );
}