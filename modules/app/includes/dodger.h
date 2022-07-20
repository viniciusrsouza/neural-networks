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

private:
  Core::ResourceManager m_ResourceManager;
  Core::Shader *m_Shader;
  Player m_Player;
  ObjectBuffer m_ObjectBuffer;
};