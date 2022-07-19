#include <iostream>

#include <window.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace Core;

Window::Window(int width, int height, const char *title)
{
  m_title = title;
  m_width = width;
  m_height = height;

  m_render_function = nullptr;
  m_update_function = nullptr;
}

Window::Window() : Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Window")
{
}

Window::~Window()
{
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (m_init_function)
  {
    m_init_function();
  }
}

void Window::Loop()
{
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

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
  if (m_update_function)
  {
    m_update_function(dt);
  }
}

void Window::Render()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  if (m_render_function)
  {
    m_render_function();
  }
}

bool Window::KeyPressed(int key)
{
  return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
}

void Core::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}