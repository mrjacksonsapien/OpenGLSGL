#pragma once

#include <glm/glm.hpp>

class Transform {
    public:
        glm::vec3 position, rotation, scale;
        Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
};