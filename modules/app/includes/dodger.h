#pragma once
#include <core.h>
#include "player.h"

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
  Core::Object m_Entity;
  Player m_Player;
};