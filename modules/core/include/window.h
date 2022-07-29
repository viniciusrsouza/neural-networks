#pragma once
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <keyboard_manager.h>

namespace Core
{
  typedef std::function<void(float)> update_fn;
  typedef std::function<void()> render_fn;
  typedef std::function<void()> init_fn;

  void framebuffer_size_callback(GLFWwindow* window, int width, int height);

  class Window
  {

  public:
    Window(int width, int height, const char *title);
    Window();
    ~Window();

    void OnUpdate(update_fn function);
    void OnRender(render_fn function);
    void OnInit(init_fn function);
    void Loop();
    void Init();
    void Close();
    int GetWidth();
    int GetHeight();
    float GetTime();
    
    void RegisterKeys(std::vector<int> keys);
    bool KeyPressed(int key);
    bool KeyDown(int key);
    bool KeyUp(int key);

  private:
    update_fn m_update_function;
    render_fn m_render_function;
    init_fn m_init_function;
    KeyboardManager *m_KeyboardManager;
    const char *m_title;
    int m_width;
    int m_height;

    void Update(float dt);
    void Render();
  };
}