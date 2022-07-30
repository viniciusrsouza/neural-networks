#pragma once
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"

namespace Core
{
  class Primitives
  {
  public:
    static Core::Triangle EQ_TRIANGLE;
    static Core::Rectangle SQUARE;
    static Core::Circle CIRCLE;
  };
}