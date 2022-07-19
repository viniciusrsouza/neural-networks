#include <primitives/triangle.h>
#include <glad/glad.h>

using namespace Core;

Triangle::Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
  m_a = a;
  m_b = b;
  m_c = c;

  m_vertices[0] = a.x; m_vertices[1] = a.y; m_vertices[2] = a.z;
  m_vertices[3] = b.x; m_vertices[4] = b.y; m_vertices[5] = b.z;
  m_vertices[6] = c.x; m_vertices[7] = c.y; m_vertices[8] = c.z;
}

Triangle::~Triangle()
{
}

void Triangle::Bind()
{
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Triangle::Draw(Shader *shader) const
{
  if (shader)
    shader->Use();
  glBindVertexArray(m_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}