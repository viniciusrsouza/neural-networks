#include <iostream>

#include <core.h>

#include "dodger.h"

int main()
{
  Core::Window window(1280, 720, "Neural Networks");
  Dodger game = Dodger(&window);

  window.Init();
  game.Init();

  window.OnUpdate([&game](float dt) {
    game.ProcessInput(dt);
    game.Update(dt); 
  });

  window.OnRender([&game]() {
    game.Render(); 
  });

  window.Loop();

  return 0;
}