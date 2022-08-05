#include <font_manager.h>
#include <iostream>
#include <glad/glad.h>
#include <string>

using namespace Core;

FontManager::FontManager(ResourceManager *resources)
{
  m_Resources = resources;
  if (FT_Init_FreeType(&m_library))
  {
    std::cout << "Failed to initialize FreeType" << std::endl;
    return;
  }
}

void FontManager::SetShader(Shader *shader)
{
  m_Shader = shader;
}

void FontManager::LoadFont(const char *path, int size)
{
  FT_Face face;
  if (FT_New_Face(m_library, m_Resources->GetPath(path).c_str(), 0, &face))
  {
    std::cerr << "Failed to load font" << std::endl;
    return;
  }
  FT_Set_Pixel_Sizes(face, 0, size);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  for (u_char c = 0; c < 128; c++)
  {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cerr << "Failed to load glyph" << std::endl;
      continue;
    }
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Character *character = new Character{
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      static_cast<unsigned int>(face->glyph->advance.x)
    };
    m_Characters.insert(std::pair<GLchar, Character*>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  FT_Done_Face(face);
  FT_Done_FreeType(m_library);
}

void FontManager::Bind()
{
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

// For some reason, this function triggers a warning when the text contains a blank space.
// I still couldn't figure out why, but since it's not really affecting the program, 
// I'm leaving this comment so I can -- HOPEFULLY -- come back to this later.
// 
// The warning is:
// UNSUPPORTED (log once): POSSIBLE ISSUE: unit 0 GLD_TEXTURE_INDEX_2D is unloadable and bound to sampler type (Float) - using zero texture because texture unloadable
void FontManager::RenderText(const std::string &text, float x, float y, float r, float g, float b, float scale)
{
  m_Shader->Use();
  glUniform1i(glGetUniformLocation(m_Shader->ID, "text"), 0);
  glUniform3f(glGetUniformLocation(m_Shader->ID, "textColor"), r, g, b);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(m_VAO);

  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character *ch = m_Characters[*c];
    float xpos = x + ch->Bearing.x * scale;
    float ypos = y - (ch->Size.y - ch->Bearing.y) * scale;
    float w = ch->Size.x * scale;
    float h = ch->Size.y * scale;
    float vertices[6][4] = {
      { xpos,     ypos + h, 0.0f, 0.0f },
      { xpos,     ypos,     0.0f, 1.0f },
      { xpos + w, ypos,     1.0f, 1.0f },

      { xpos,     ypos + h, 0.0f, 0.0f },
      { xpos + w, ypos,     1.0f, 1.0f },
      { xpos + w, ypos + h, 1.0f, 0.0f }
    };
    glBindTexture(GL_TEXTURE_2D, ch->TextureID);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    x += (ch->Advance >> 6) * scale;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 FontManager::GetTextSize(const std::string &text, float scale)
{
  glm::vec2 size(0.0f);
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character *ch = m_Characters[*c];
    size.x += ch->Size.x * scale;
    size.y = std::max(size.y, ch->Size.y * scale);
  }
  return size;
}