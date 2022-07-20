#include <game.h>
#include <window.h>

using namespace Core;

Game::Game(Window* window)
{
  m_State = GAME_ACTIVE;
  m_Window = window;
}

Game::~Game()
{
}