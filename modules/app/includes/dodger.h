#pragma once
#include <core.h>
#include "player.h"
#include "object_buffer.h"

class Dodger : public Core::Game
{
public:
  Dodger(Core::Window *window);
  ~Dodger();

  void Init();
  void Exit();
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();
  void RenderPause();
  void RenderUI();

private:
  Core::Shader *m_Shader;
  Core::Shader *m_FontShader;
  Player m_Player;
  ObjectBuffer m_ObjectBuffer;

  float m_FrameTime;
};