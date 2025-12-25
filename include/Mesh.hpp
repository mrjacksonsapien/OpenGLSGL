#pragma once

#include "Node.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"

class Mesh : Node {
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<Triangle>& triangles);
};
