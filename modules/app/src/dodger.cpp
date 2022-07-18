#include <iostream>

#include "dodger.h"

Dodger::Dodger(Core::Window* window) : Core::Game(window)
{
}

Dodger::~Dodger()
{
}

void Dodger::Init()
{
}
void Dodger::Exit()
{
  m_window->Close();
}
void Dodger::ProcessInput(float dt)
{
  if (m_window->KeyPressed(KEY_ESCAPE))
  {
    m_state = Core::GameState::GAME_CLOSE;
  }
}
void Dodger::Update(float dt)
{
  if (m_state == Core::GameState::GAME_CLOSE)
  {
    Exit();
  }
}
void Dodger::Render()
{
}