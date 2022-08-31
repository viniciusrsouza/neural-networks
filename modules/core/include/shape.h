#pragma once

#include <shader.h>

namespace Core
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    
    virtual void Bind() = 0;
    virtual void Draw(Shader *shader = nullptr) const = 0;

    virtual bool Intersects(glm::vec2 p, glm::vec2 p1, glm::vec2 p2, glm::mat4 ortho) const = 0;
  };
}