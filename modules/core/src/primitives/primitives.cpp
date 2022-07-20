#include <primitives/primitives.h>

using namespace Core;

Triangle Primitives::EQ_TRIANGLE(
    glm::vec2(-1.0f, -1.0f),
    glm::vec2(1.0f, -1.0f),
    glm::vec2(0.0f, 1.0f));

Rectangle Primitives::SQUARE(
    glm::vec2(-1.0f, -1.0f),
    glm::vec2(1.0f, -1.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(-1.0f, 1.0f));