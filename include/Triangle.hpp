#pragma once

#include "Vertex.hpp"

class Triangle {
    Vertex a;
    Vertex b;
    Vertex c;
public:
    Triangle(const Vertex& a, const Vertex& b, const Vertex& c);

    Vertex getVertexA() const;
    Vertex getVertexB() const;
    Vertex getVertexC() const;
};
