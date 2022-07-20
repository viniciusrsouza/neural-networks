#include <iostream>

#include "dodger.h"

Dodger::Dodger(Core::Window* window) : Core::Game(window), 
  m_Player(glm::vec2(300.0f, 300.0f)), 
  m_ResourceManager("./modules/app/resources/"),
  m_ObjectBuffer(window->GetWidth(), window->GetHeight())
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
  Core::Primitives::SQUARE.Bind();
  m_Player.Bind();
}

void Dodger::Exit()
{
  m_Window->Close();
}
void Dodger::ProcessInput(float dt)
{
  if (m_Window->KeyPressed(KEY_ESCAPE))
    m_State = Core::GameState::GAME_CLOSE;
  if (m_Window->KeyPressed(KEY_SPACE))
    m_Player.Jump();
}
void Dodger::Update(float dt)
{
  if (m_State == Core::GameState::GAME_CLOSE)
  {
    Exit();
  }

  m_Player.Update(dt, m_Window->GetHeight());
  m_ObjectBuffer.Update(dt, m_Window->GetTime());
}
void Dodger::Render()
{
  glm::mat4 projection = glm::ortho(
    0.0f,
    static_cast<float>(m_Window->GetWidth()),
    static_cast<float>(m_Window->GetHeight()),
    0.0f,
    -1.0f,
    1.0f
  );
  m_Shader->Use();
  m_Shader->SetMatrix4("projection", projection);
  m_Player.Draw(m_Shader);
  m_ObjectBuffer.Render(m_Shader);
}