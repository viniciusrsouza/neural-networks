#include <keyboard_manager.h>

using namespace Core;

KeyboardManager::KeyboardManager(GLFWwindow* ctx)
{
  m_Ctx = ctx;
  for (int i = 0; i < KEY_LAST; i++)
  {
    m_Keys[i] = false;
    m_PrevKeys[i] = false;
    m_ShouldWatch[i] = false;
  }
}

KeyboardManager::~KeyboardManager()
{
}

bool KeyboardManager::IsKeyPressed(int key)
{
  return m_Keys[key];
}

bool KeyboardManager::IsKeyDown(int key)
{
  return m_Keys[key] && !m_PrevKeys[key];
}

bool KeyboardManager::IsKeyUp(int key)
{
  return !m_Keys[key] && m_PrevKeys[key];
}

void KeyboardManager::RegisterKeys(std::vector<int> keys)
{
  for (int key : keys)
  {
    m_ShouldWatch[key] = true;
  }
}

void KeyboardManager::Process()
{
  for (int key = 0; key < KEY_LAST; ++key)
  {
    m_PrevKeys[key] = m_Keys[key];
  }
  for (int key = 0; key < KEY_LAST; ++key)
  {
    m_Keys[key] = glfwGetKey(m_Ctx, key) == GLFW_PRESS;
  }
}