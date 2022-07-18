#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
  if (glfwGetKey(m_window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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