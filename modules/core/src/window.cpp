#include <iostream>

#include <window.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace Core;

Window::Window(int width, int height, const char *title, const char *resources)
{
  m_title = title;
  m_width = width;
  m_height = height;

  m_render_function = nullptr;
  m_update_function = nullptr;
  Resources = new ResourceManager(resources);
}

Window::Window() : Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Window", "./")
{
}

Window::~Window()
{
  delete Keyboard;
  delete Font;
  delete Resources;
}

void Window::OnUpdate(update_fn function)
{
  m_update_function = function;
}

void Window::OnRender(render_fn function)
{
  m_render_function = function;
}

void Window::OnInit(init_fn function)
{
  m_init_function = function;
}

void Window::Init()
{
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  std::cout << "Apple system, runnning in compat mode." << std::endl;
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_RESIZABLE, false);

  GLFWwindow *window = glfwCreateWindow(this->m_width, this->m_height, this->m_title, nullptr, nullptr);

  if (!window)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }

  unsigned int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
  unsigned int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
  std::cout << "Shader version: " << major << "." << minor << std::endl;

  std::cout << "Initialized OpenGL context" << std::endl;
  std::cout << glGetString(GL_VERSION) << std::endl;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  Keyboard = new KeyboardManager(window);
  Font = new FontManager(Resources);

  if (m_init_function)
  {
    m_init_function();
  }
}

void Window::Loop()
{
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(glfwGetCurrentContext()))
  {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwPollEvents();
    Update(deltaTime);
    Render();
    glfwSwapBuffers(glfwGetCurrentContext());
  }
}

void Window::Close()
{
  glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}

void Window::Update(float dt)
{
  Keyboard->Process();
  if (m_update_function)
  {
    m_update_function(dt);
  }
}

void Window::Render()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if (m_render_function)
  {
    m_render_function();
  }
}

int Window::GetWidth()
{
  return m_width;
}

int Window::GetHeight()
{
  return m_height;
}

float Window::GetTime()
{
  return glfwGetTime();
}

void Core::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}