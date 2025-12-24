#pragma once

#include <glm/glm.hpp>

class Vertex {
public:
    Vertex(const glm::vec3& position);

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& position);

private:
    glm::vec3 position;
};
