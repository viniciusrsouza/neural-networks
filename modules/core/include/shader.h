#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Core
{
  class Shader
  {
  public:
    unsigned int ID;
    Shader();
    ~Shader();

    void Use() const;
    void Compile(const char *vertexCode, const char *fragmentCode);

    // Uniforms
    void SetFloat(const char *name, float value) const;
    void SetInteger(const char *name, int value) const;
    void SetVector2f(const char *name, float x, float y) const;
    void SetVector2f(const char *name, const glm::vec2 &value) const;
    void SetVector3f(const char *name, float x, float y, float z) const;
    void SetVector3f(const char *name, const glm::vec3 &value) const;
    void SetVector4f(const char *name, float x, float y, float z, float w) const;
    void SetVector4f(const char *name, const glm::vec4 &value) const;
    void SetMatrix4(const char *name, const glm::mat4 &matrix) const;

  private:
    void CheckCompileErrors(unsigned int shader, std::string type);
  };
}