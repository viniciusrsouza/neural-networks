#pragma once

namespace Core
{
  class Window
  {

  public:
    Window(int width, int height, const char *title);
    Window();
    ~Window();

    void OnUpdate(void (*function)(float dt));
    void OnRender(void (*function)());
    void Loop();
    void Init();
    void Close();

  private:
    void (*m_update_function)(float dt);
    void (*m_render_function)();
    const char *m_title;
    int m_width;
    int m_height;

    void Update(float dt);
    void Render();
  };
}