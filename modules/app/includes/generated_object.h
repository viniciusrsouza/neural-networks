#pragma once
#include <core.h>

class GeneratedObject: public Core::Object
{
public:
  GeneratedObject(Core::Shape *shape, glm::vec2 position, glm::vec2 scale, float rotation, float speed);
  ~GeneratedObject();

  void Update(float dt);

private:
  float m_Speed;
};