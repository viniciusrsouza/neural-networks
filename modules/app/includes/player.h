#pragma once
#include <core.h>
#include <glm/gtc/type_ptr.hpp>

class Player: public Core::Object
{
public:
  Player();
  Player(glm::vec2 position);
  ~Player();

  glm::vec2 GetPosition() const;
  virtual void Bind();
  void Update(float dt, float yBoundary);
  void Jump();

private:
  Player(glm::vec2 position, Core::Shape *shape);
  float m_Velocity;
  float m_Acceleration;
  float m_Size;

  // validate
  float m_Gravity;
  float m_JumpSpeed;
  float m_MaxSpeed;
  
  bool m_IsJumping;
};