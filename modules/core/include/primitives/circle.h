#pragma once
#include <shape.h>
#include <shader.h>
#include <vector>

namespace Core
{
  class Circle: public Shape
  {
  public:
    Circle(glm::vec2 center, float radius, float segments);
    
    virtual void Bind();
    virtual void Draw(Shader *shader = nullptr) const;
  
  private:
    glm::vec2 m_Center;
    float m_Radius;
    float m_Segments;
    
    std::vector<float> m_Vertices;
    unsigned int m_VBO, m_VAO;
  };
}