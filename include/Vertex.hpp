#pragma once

#include <glm/glm.hpp>

class Vertex {
    glm::vec3 position;
public:
    Vertex(const glm::vec3& position);

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& newPosition);
};
