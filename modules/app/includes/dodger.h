#pragma once
#include <core.h>

class Dodger : public Core::Game
{
public:
  Dodger(Core::Window* window);
  ~Dodger();

  void Init();
  void Exit();
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();
};