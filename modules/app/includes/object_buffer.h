#include <core.h>
#include <vector>
#include "generated_object.h"

class ObjectBuffer
{
public:
  ObjectBuffer(int width, int height);
  ~ObjectBuffer();

  void Generate();
  void Update(float dt, float ellapsedTime);
  void Render(Core::Shader *shader);

private:
  int m_Width;
  int m_Height;
  
  float m_Speed;
  float m_GenerateTime;
  float m_GenerationSpeed;
  std::vector<GeneratedObject*> m_Objects;
};