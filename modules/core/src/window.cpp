#include <iostream>

#include <window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

void Window::OnUpdate(void (*function)(float dt))
{
  m_update_function = function;
}

void Window::OnRender(void (*function)())
{
  m_render_function = function;
}

void Window::Init()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_RESIZABLE, false);

  GLFWwindow *window = glfwCreateWindow(this->m_width, this->m_height, this->m_title, nullptr, nullptr);
  glfwMakeContextCurrent(window);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }

  // glfwSetKeyCallback(window, key_callback);
  // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // OpenGL configuration
  // --------------------
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
  glfwTerminate();
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
  if (m_render_function)
  {
    m_render_function();
  }
}