#include <player.h>
#include <iostream>

Player::Player() : Player(glm::vec2(100.0f, 100.0f))
{
}

Player::Player(glm::vec2 position) : Core::Object(&Core::Primitives::SQUARE, position, glm::vec2(20.0f, 20.0f), 180.0f),
                                     m_Size(20.0f),
                                     m_JumpSpeed(-20.0f),
                                     m_IsJumping(false),
                                     m_Velocity(0.0f),
                                     m_Acceleration(0.0f),
                                     m_Gravity(-2.0f),
                                     m_MaxSpeed(500.0f)
{
}

Player::~Player()
{
}

void Player::Update(float dt, float yBoundary)
{
  if (m_IsJumping)
  {
    m_Acceleration = m_JumpSpeed;
    m_IsJumping = false;
    if (m_Velocity > 0.0f)
      m_Velocity = 0.0f;
  }
  else
  {
    m_Acceleration -= m_Gravity;
  }

  m_Velocity += m_Acceleration;
  if (m_Velocity > m_MaxSpeed)
    m_Velocity = m_MaxSpeed;
  if (m_Velocity < -m_MaxSpeed)
    m_Velocity = -m_MaxSpeed;
  m_Position.y += m_Velocity * dt;
  if ((m_Position.y + m_Size) > yBoundary)
  {
    m_Position.y = yBoundary - m_Size;
    m_Velocity = 0.0f;
  }
  else if ((m_Position.y - m_Size) < 0.0f)
  {
    m_Position.y = m_Size;
    m_Velocity = 0.0f;
    m_Acceleration = 0.0f;
  }
}

void Player::Jump()
{
  m_IsJumping = true;
}

glm::vec2 Player::GetPosition() const
{
  return glm::vec2(m_Position);
}