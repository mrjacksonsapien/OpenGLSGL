#include "Vertex.hpp"

Vertex::Vertex(const glm::vec3& position)
    : position(position) {}

glm::vec3 Vertex::getPosition() const {
    return position;
}

void Vertex::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
}
