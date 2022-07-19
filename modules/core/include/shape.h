#pragma once

#include <shader.h>

namespace Core
{
  class Shape
  {
  public:
    Shape();
    ~Shape();
    
    virtual void Bind() = 0;
    virtual void Draw(Shader *shader = nullptr) const = 0;
  };
}