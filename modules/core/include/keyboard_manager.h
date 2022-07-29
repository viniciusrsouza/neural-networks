#pragma once
#include <vector>
#include "keys.h"
#include <GLFW/glfw3.h>

namespace Core
{
  class KeyboardManager
  {
  public:
    KeyboardManager(GLFWwindow* ctx);
    ~KeyboardManager();

    void RegisterKeys(std::vector<int> keys);
    void Process();
    bool IsKeyPressed(int key);
    bool IsKeyDown(int key);
    bool IsKeyUp(int key);


  private:
    bool m_Keys[KEY_LAST];
    bool m_PrevKeys[KEY_LAST];
    bool m_ShouldWatch[KEY_LAST];
    GLFWwindow* m_Ctx;
  };
}