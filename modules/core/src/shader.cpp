#include <iostream>
#include <glad/glad.h>
#include <shader.h>

using namespace Core;

Shader::Shader() : ID(0)
{
}

Shader::~Shader()
{
  glDeleteProgram(ID);
}

void Shader::Use() const
{
  glUseProgram(ID);
}

void Shader::Compile(const char *vertexCode, const char *fragmentCode)
{
  unsigned int sVertex, sFragment, gShader;
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexCode, NULL);
  glCompileShader(sVertex);
  CheckCompileErrors(sVertex, "VERTEX");

  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentCode, NULL);
  glCompileShader(sFragment);
  CheckCompileErrors(sFragment, "FRAGMENT");

  ID = glCreateProgram();
  glAttachShader(ID, sVertex);
  glAttachShader(ID, sFragment);

  glLinkProgram(ID);
  CheckCompileErrors(ID, "PROGRAM");

  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
}

void Shader::CheckCompileErrors(unsigned int object, std::string type)
{
  int success;
  char infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
    }
  }
  else
  {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
    }
  }
}

// Uniforms
void Shader::SetFloat(const char *name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetInteger(const char *name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetVector2f(const char *name, float x, float y) const
{
  glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void Shader::SetVector2f(const char *name, const glm::vec2 &value) const
{
  glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char *name, float x, float y, float z) const
{
  glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::SetVector3f(const char *name, const glm::vec3 &value) const
{
  glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char *name, float x, float y, float z, float w) const
{
  glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::SetVector4f(const char *name, const glm::vec4 &value) const
{
  glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}