#pragma once
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
  typedef std::function<void(float)> update_fn;
  typedef std::function<void()> render_fn;

  class Window
  {

  public:
    Window(int width, int height, const char *title);
    Window();
    ~Window();

    void OnUpdate(update_fn function);
    void OnRender(render_fn function);
    void Loop();
    void Init();
    void Close();
    
    bool KeyPressed(int key);

  private:
    update_fn m_update_function;
    render_fn m_render_function;
    const char *m_title;
    int m_width;
    int m_height;

    void Update(float dt);
    void Render();
  };
}