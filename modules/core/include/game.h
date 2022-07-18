#include "window.h"

namespace Core
{
  enum GameState
  {
    GAME_ACTIVE,
    GAME_PAUSED,
    GAME_CLOSE,
  };

  class Game
  {
  public:
    Game(Window* window);
    ~Game();

    virtual void Init(){};
    virtual void Exit(){};
    virtual void ProcessInput(float dt){};
    virtual void Update(float dt){};
    virtual void Render(){};

  protected:
    GameState m_state;
    Window *m_window;
  };
}