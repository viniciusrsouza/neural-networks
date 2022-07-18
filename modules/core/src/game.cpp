#include <game.h>
#include <window.h>

using namespace Core;

Game::Game(Window* window)
{
  m_state = GAME_ACTIVE;
  m_window = window;
}

Game::~Game()
{
}