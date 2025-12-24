#pragma once

#include "Node.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"

class Mesh : Node {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<Triangle>& triangles);

private:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
};
