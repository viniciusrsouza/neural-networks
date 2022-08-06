#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include "shader.h"

namespace Core
{
  struct Ray
  {
    glm::vec2 origin;
    glm::vec2 direction;
  };

  struct Line
  {
    ~Line();
    unsigned int VAO, VBO;
    float data[4];
    glm::vec2 start;
    glm::vec2 end;
    glm::vec3 color;
  };

  class RayCaster
  {
  public:
    RayCaster(int width, int height);
    ~RayCaster();

    void Cast(Ray ray);
    void Cast(glm::vec2 origin, glm::vec2 direction);

    void Draw(Shader *shader);
    void Clear();
  
  private:
    int m_Width;
    int m_Height;
    std::vector<Line*> m_Lines;
  };
}