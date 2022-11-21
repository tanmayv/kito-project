#pragma once
#include "result.h"
#include <glm/glm.hpp>

namespace kito {
typedef unsigned int ActorId;
typedef glm::fvec4 Color;
typedef glm::fvec4 Vec4;
typedef glm::fmat4x4 Mat4x4;
static const glm::mat4 IDENTITY = glm::mat4x4{};
static const glm::vec4 WHITE = glm::fvec4(1.0f);
}  // namespace kito
