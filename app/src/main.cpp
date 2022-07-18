#include <iostream>

#include <core.h>

int main()
{
  Core::Window window(1280, 720, "Neural Networks");

  window.Init();
  window.Loop();

  return 0;
}