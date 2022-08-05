#include <iostream>
#include <vector>
#include <sstream>

#include "dodger.h"

Dodger::Dodger(Core::Window* window) : Core::Game(window), 
  m_Player(glm::vec2(300.0f, 300.0f)), 
  m_ObjectBuffer(window->GetWidth(), window->GetHeight())
{
  m_Shader = new Core::Shader();
  m_FontShader = new Core::Shader();
}

Dodger::~Dodger()
{
  delete m_Shader;
  delete m_FontShader;
}

void Dodger::Init()
{
  m_Window->Keyboard->RegisterKeys(std::vector<int>({
    KEY_ESCAPE, KEY_SPACE, KEY_Q
  }));
  m_Shader->Compile(
    m_Window->Resources->ReadFile("shaders/default/vertex.glsl").c_str(),
    m_Window->Resources->ReadFile("shaders/default/fragment.glsl").c_str()
  );
  m_FontShader->Compile(
    m_Window->Resources->ReadFile("shaders/font/vertex.glsl").c_str(),
    m_Window->Resources->ReadFile("shaders/font/fragment.glsl").c_str()
  );

  m_FontShader->Use();
  m_Window->Font->SetShader(m_FontShader);
  m_Window->Font->LoadFont("fonts/Cascadia.ttf", 32);
  m_Window->Font->Bind();

  glm::mat4 fontProjection = glm::ortho(
      0.0f, static_cast<float>(m_Window->GetWidth()), 
      0.0f, static_cast<float>(m_Window->GetHeight())
  );
  m_FontShader->SetMatrix4("projection", fontProjection);

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

  Core::Primitives::SQUARE.Bind();
  Core::Primitives::CIRCLE.Bind();
  m_Player.Bind();
}

void Dodger::Exit()
{
  m_Window->Close();
}
void Dodger::ProcessInput(float dt)
{
  if (m_Window->Keyboard->IsKeyUp(KEY_ESCAPE)) {
    if (m_State == Core::GameState::GAME_ACTIVE)
      m_State = Core::GameState::GAME_PAUSED;
    else if (m_State == Core::GameState::GAME_PAUSED)
      m_State = Core::GameState::GAME_ACTIVE;
  }
  if (m_Window->Keyboard->IsKeyPressed(KEY_SPACE))
  {
    m_Player.Jump();
  }
  if (m_Window->Keyboard->IsKeyUp(KEY_Q) && (m_State == Core::GameState::GAME_PAUSED || m_State == Core::GameState::GAME_OVER))
    m_State = Core::GameState::GAME_CLOSE;
}
void Dodger::Update(float dt)
{
  
  if (m_State == Core::GameState::GAME_CLOSE)
  {
    Exit();
  }
  else if (m_State == Core::GameState::GAME_ACTIVE)
  {
    m_Player.Update(dt, m_Window->GetHeight());
    m_ObjectBuffer.Update(dt, m_Window->GetTime());

    if (m_Player.Collides(&m_ObjectBuffer))
    {
      m_State = Core::GameState::GAME_OVER;
    }
  }

  if (m_State == Core::GameState::GAME_ACTIVE)
    m_FrameTime = dt;
}

void Dodger::RenderUI()
{
  std::stringstream ss;
  ss << "Frame Time: " << m_FrameTime << "ms";
  ss << " | ";
  ss << 1.0f / m_FrameTime << "fps";
  m_Window->Font->RenderText(ss.str(), 10, 10, 1.0f, 1.0f, 1.0f, 0.5f);
}

void Dodger::RenderPause()
{
  auto size = m_Window->Font->GetTextSize("PAUSED", 1.0f);
  m_Window->Font->RenderText("PAUSED",
    m_Window->GetWidth() / 2 - size.x / 2,
    m_Window->GetHeight() / 2 - size.y / 2,
    1.0f, 0.5f, 0.5f, 1.0f
  );
}

void Dodger::Render()
{
  RenderUI();
  if (m_State == Core::GameState::GAME_PAUSED)
  {
    RenderPause();
  }
  m_Shader->Use();
  m_Player.Draw(m_Shader);
  m_ObjectBuffer.Render(m_Shader);
}