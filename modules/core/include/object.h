#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shape.h"

namespace Core
{
  class Object
  {
  public:
    Object(Shape *shape);
    ~Object();
    
    virtual void Draw() const = 0;
    glm::vec3 GetPosition() const;
  
  protected:
    Shape *m_shape;
    glm::vec3 m_position;
  };
}