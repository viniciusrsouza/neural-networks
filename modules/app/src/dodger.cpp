#include <iostream>

#include "dodger.h"

Dodger::Dodger(Core::Window* window) : Core::Game(window), 
  m_Entity(&Primitives::EQ_TRIANGLE, glm::vec2(300.0f, 300.0f), glm::vec2(100.0f, 100.0f), 180.0f), 
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
  Primitives::EQ_TRIANGLE.Bind();
  m_Entity.Bind();
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
  glm::mat4 projection = glm::ortho(
    0.0f,
    static_cast<float>(m_window->GetWidth()),
    static_cast<float>(m_window->GetHeight()),
    0.0f,
    -1.0f,
    1.0f
  );
  m_Shader->Use();
  m_Shader->SetMatrix4("projection", projection);
  m_Entity.Draw(m_Shader);
}