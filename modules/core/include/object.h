#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shape.h"
#include "shader.h"

namespace Core
{
  class Object
  {
  public:
    Object(Shape *shape);
    Object(Shape *shape, glm::vec2 position, glm::vec2 scale, float rotation);
    ~Object();
    
    virtual void Bind();
    void Draw(Shader *shader) const;
    glm::vec2 GetPosition() const;
  
  protected:
    Shape *m_Shape;
    glm::vec2 m_Position;
    glm::vec2 m_Scale;
    float m_Rotation;
  };
}