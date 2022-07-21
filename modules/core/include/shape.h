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
  };
}