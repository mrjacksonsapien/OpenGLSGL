#pragma once

#include <glm/glm.hpp>

class Transform {
    private:
        glm::vec3 position, orientation, scale;
        Transform(glm::vec3 position, glm::vec3 orientation, glm::vec3 scale);
};