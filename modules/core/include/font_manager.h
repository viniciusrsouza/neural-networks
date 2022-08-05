#pragma once
#include <vector>
#include <map>
#include <iostream>

#include "resource_manager.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Core
{
  struct Character {
    ~Character()
    {
      std::cout << "testeee" << std::endl;
    }
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
  };

  class FontManager
  {
  public:
    FontManager(ResourceManager *resources);

    void LoadFont(const char *path, int size);
    void Bind();
    void RenderText(const std::string &text, float x, float y, float r, float g, float b, float scale);
    void SetShader(Shader *shader);
    glm::vec2 GetTextSize(const std::string &text, float scale);
  
  private:
    FT_Library m_library;
    ResourceManager *m_Resources;
    Shader *m_Shader;
    std::map<char, Character*> m_Characters;
    unsigned int m_VAO, m_VBO;
  };
}