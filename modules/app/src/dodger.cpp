#include <iostream>

#include "dodger.h"

Dodger::Dodger(Core::Window* window) : Core::Game(window), 
  m_Triangle(Primitives::EQ_TRIANGLE), 
  m_ResourceManager("./modules/app/resources/")
{
  m_Shader = new Core::Shader();
}

Dodger::~Dodger()
{
  delete m_Shader;
}

void Dodger::Init()
{
  m_Shader->Compile(
    m_ResourceManager.ReadFile("shaders/default/vertex.glsl").c_str(),
    m_ResourceManager.ReadFile("shaders/default/fragment.glsl").c_str()
  );
  m_Triangle.Bind();
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
  m_Triangle.Draw(m_Shader);
}